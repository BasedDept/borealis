/**
 * @file crt1.c
 * @brief C runtime for boot stub
 * @author George Witt
 * @date 2024-03-02
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <errno.h>
#include <panic.h>
#include <libfdt.h>
#include "libfdt_env.h"

extern noreturn void _halt(void);
extern int main(int argc, char **argv);
extern struct fdt_header *g_fdt;
extern void adainit(void);
extern void adafinal(void);

struct args {
    int argc;
    char **argv;
};

enum quotes {
    QUOTE_NONE = 0,
    QUOTE_SINGLE,
    QUOTE_DOUBLE,
    QUOTE_DOLLARSINGLE
};

// NOLINTNEXTLINE(cert-dcl37-c)
unsigned long __stack_chk_guard;

static inline enum quotes quote_next_state(enum quotes state, const char **s_p)
{
    enum quotes out = state;
    while (**s_p != '\0') {
        switch (out) {
            case QUOTE_NONE:
                if (**s_p == '\'') {
                    out = QUOTE_SINGLE;
                    (*s_p) ++;
                    continue;
                }
                else if (**s_p == '"') {
                    out = QUOTE_DOUBLE;
                    (*s_p) ++;
                    continue;
                }
                else if (**s_p == '$' && *(*s_p + 1) == '\'') {
                    out = QUOTE_DOLLARSINGLE;
                    (*s_p) += 2;
                    continue;
                }
                return out;
            case QUOTE_SINGLE:
            case QUOTE_DOLLARSINGLE:
                if (**s_p == '\'') {
                    out = QUOTE_NONE;
                    (*s_p) ++;
                    continue;
                }
                return out;
            case QUOTE_DOUBLE:
                if (**s_p == '"') {
                    out = QUOTE_NONE;
                    (*s_p) ++;
                    continue;
                }
                return out;
            default:
                break;
        }
    }
    return out;
}

static inline char parse_circumflex(char c)
{
    static_assert('\xff' > 0, "char must be an unsigned type");
    return toupper(c) - 128;
}

static inline char parse_hex_byte(const char *s)
{
    assert(s != NULL);
    char out = 0;
    for (ptrdiff_t i = 0; i < 2; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            out |= (s[i] - '0') << 4;
        }
        else if (toupper(s[i]) >= 'A' && s[i] <= 'F') {
            out |= (s[i] - 'A') << 4;
        }
        else panic(EINVAL, "Invalid character in hex string.");
    }
    return out;
}

static inline char parse_oct_byte(const char *s)
{
    assert(s != NULL);
    unsigned int out = 0;
    for (ptrdiff_t i = 0; i < 2; i++) {
        if (s[0] >= '0' && s[0] <= '7') {
            out |= (s[0] - '0') << 6;
        }
        else panic(EINVAL, "Invalid character in oct string.");
    }
    if (out > 255) panic(EINVAL, "Value is too large for character.");
    return (char)out;
}

static inline void expand_c_escape_code(char **out_p, const char **in_p)
{
    switch (**in_p) {
        case '"':
            **out_p = '"';
            break;
        case '\'':
            **out_p = '\'';
            break;
        case '\\':
            **out_p = '\\';
            break;
        case 'a':
            **out_p = '\a';
            break;
        case 'b':
            **out_p = '\b';
            break;
        case 'e':
            **out_p = '\x1b';
            break;
        case 'f':
            **out_p = '\f';
            break;
        case 'n':
            **out_p = '\n';
            break;
        case 'r':
            **out_p = '\r';
            break;
        case 't':
            **out_p = '\t';
            break;
        case 'v':
            **out_p = '\v';
            break;
        case 'c':
            (*in_p) ++;;
            if (**in_p == '\\') (*in_p) ++;;
            **out_p = parse_circumflex(**in_p);
            break;
        case 'x':
            (*in_p) ++;
            **out_p = parse_hex_byte(*in_p);
            (*in_p) ++;
            return;
        default:
            if (**in_p >= '0' && **in_p <= '7') {
                (*in_p) ++;
                **out_p = parse_oct_byte(*in_p);
                (*in_p) += 2;
                return;
            }
            panic(EINVAL, "Invalid character was escaped.");
    }

    (*out_p) ++;
    (*in_p) ++;
}

struct args
parse_kernel_cmdline(const char *cmdline, size_t l, char *buf, size_t n)
{
    if (cmdline == NULL || buf == NULL) return (struct args){.argc = 0,
                                                             .argv = NULL};
    memset(buf, 0, n);
    char *l_buf = buf;
    const char *l_cmdline = cmdline;
    char **argv = (char **)(buf + l);
    ptrdiff_t n_argv = (n - l) / sizeof(char *);
    int argc = 0;

    enum quotes quoting_state = QUOTE_NONE;
    char *word = l_buf;
    do {
        quoting_state = quote_next_state(quoting_state, &l_cmdline);
        switch (quoting_state) {
            case QUOTE_SINGLE:
                break;
            case QUOTE_DOUBLE:
                if (*l_cmdline == '\\') {
                    l_cmdline ++;
                    if (*l_cmdline == '\n') {
                        l_cmdline ++;
                        l_buf ++;
                        break;
                    }
                    if (*l_cmdline == '"') {
                        *l_buf = *l_cmdline;
                        l_cmdline ++;
                        l_buf ++;
                        break;
                    }
                    panic(EINVAL, "Invalid character was escaped.");
                }
                break;
            case QUOTE_DOLLARSINGLE:
                if (*l_cmdline == '\\') {
                    l_cmdline ++;
                    expand_c_escape_code(&l_buf, &l_cmdline);
                    continue;
                }
                break;
            default:
                if (*l_cmdline == '\\') {
                    l_cmdline ++;
                    if (*l_cmdline == '\n') {
                        l_cmdline ++;
                        l_buf ++;
                        continue;
                    }
                    break;
                }
                if (*l_cmdline == ' '
                    || *l_cmdline == '\t'
                    || *l_cmdline == '\n') {
                    *l_buf = '\0';
                    assert(word <= buf + n);
                    argv[(ptrdiff_t)argc] = word;
                    word = l_buf + 1;
                    argc ++;
                    if ((ptrdiff_t)argc >= n_argv)
                        panic(ENOMEM, "Not enough space for cmdline.");
                    l_cmdline ++;
                    l_buf ++;
                    continue;
                }
                break;
        }

        *l_buf = *l_cmdline;
        l_cmdline ++;
        l_buf ++;

    } while (*l_cmdline != 0 && l_cmdline - cmdline < l);

    *l_buf = '\0';
    assert(word <= buf + n);
    argv[(ptrdiff_t)argc] = word;
    word = NULL;
    argc ++;
    if ((ptrdiff_t)argc >= n_argv)
        panic(ENOMEM, "Not enough space for cmdline.");
    argv[(ptrdiff_t)argc] = word;

    return (struct args){.argc = argc, .argv = argv};
}

extern char __heap;
struct heap_frame *__hp = NULL;

// NOLINTNEXTLINE(cert-dcl37-c)
void __attribute__((no_stack_protector)) _start_c2(struct fdt_header *fdt)
{
    g_fdt = fdt;
    __stack_chk_guard = 0xDEADBEEFF00DBABE;

    if (0 != fdt_check_header(g_fdt)) {
        panic(EINVAL, "Invalid Devicetree!");
    }

    const char *cmdline = NULL;
    int cmdline_l = 0;
    int chosen_node = fdt_path_offset(g_fdt, "/chosen");
    if (chosen_node >= 0) {
        cmdline = fdt_getprop(g_fdt, chosen_node, "bootargs", &cmdline_l);
    }

    char argbuf[4096];
    struct args args =
        parse_kernel_cmdline(cmdline, cmdline_l, argbuf, sizeof(argbuf));

    __hp = (struct heap_frame *)&__heap;
    __hp->prev = NULL;

    adainit();
    (void)main(args.argc, args.argv);
    adafinal();
}

// NOLINTNEXTLINE(cert-dcl37-c)
noreturn void __stack_chk_fail(void)
{
    panic(ENOTRECOVERABLE, "Stack smashing detected!");
}

