/**
 * @file curses.h
 * @brief Definitions for screen handling and optimization functions
 * @author George Witt
 * @date 2024-09-15
 *
 * X/Open Curses, Issue 7 5 curses.h
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 202405L
#endif

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 800
#endif

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L) || \
    (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 700)
#ifndef __CURSES_H__
#define __CURSES_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define _XOPEN_CURSES

extern int COLOR_PAIRS;
extern int COLORS;
extern int COLS;
extern WINDOW *curscr;
extern int LINES;
extern WINDOW *stdscr;

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#undef __STDIO_H__
#endif
#define EOF __EOF__

#ifndef __WCHAR_H__
#define __WCHAR_H__
#include <wchar.h>
#undef __WCHAR_H__
typedef __wint_t__ wint_t;
#endif
#define WEOF __WEOF__

#ifndef __STDDEF_H__
#define __STDDEF_H__
#include <stddef.h>
#undef __STDDEF_H__
#endif
typedef __wchar_t__ wchar_t;

#define ERR (-2)
#define FALSE 0
#define KEY_CODE_YES (10)
#define OK 0
#define TRUE 1

#define bool _Bool

typedef unsigned long chtype;
typedef unsigned long attr_t;
typedef x SCREEN;
typedef x cchar_t;
typedef x WINDOW;

#define WA_ALTCHARSET (1 << 8)
#define WA_BLINK (1 << 0)
#define WA_BOLD (1 << 1)
#define WA_DIM (1 << 2)
#define WA_HORIZONTAL (1 << 12)
#define WA_INVIS (1 << 9)
#define WA_LEFT (1 << 13)
#define WA_LOW (1 << 14)
#define WA_PROTECT (1 << 10)
#define WA_REVERSE (1 << 3)
#define WA_RIGHT (1 << 15)
#define WA_STANDOUT (1 << 4)
#define WA_TOP (1 << 16)
#define WA_UNDERLINE (1 << 5)
#define WA_VERTICAL (1 << 17)

#define A_ALTCHARSET (1 << 8)
#define A_BLINK (1 << 0)
#define A_BOLD (1 << 1)
#define A_DIM (1 << 2)
#define A_INVIS (1 << 9)
#define A_PROTECT (1 << 10)
#define A_REVERSE (1 << 3)
#define A_STANDOUT (1 << 4)
#define A_UNDERLINE (1 << 5)

#define A_ATTRIBUTES (1 << 6)
#define A_CHARTEXT (1 << 7)
#define A_COLOR (1 << 11)

#define ACS_ULCORNER
#define ACS_LLCORNER
#define ACS_URCORNER
#define ACS_LRCORNER
#define ACS_RTEE
#define ACS_LTEE
#define ACS_BTEE
#define ACS_TTEE
#define ACS_HLINE
#define ACS_VLINE
#define ACS_PLUS
#define ACS_S1
#define ACS_S9
#define ACS_DIAMOND
#define ACS_CKBOARD
#define ACS_DEGREE
#define ACS_PLMINUS
#define ACS_BULLET
#define ACS_LARROW
#define ACS_RARROW
#define ACS_DARROW
#define ACS_UARROW
#define ACS_BOARD
#define ACS_LANTERN
#define ACS_BLOCK

#define WACS_ULCORNER
#define WACS_LLCORNER
#define WACS_URCORNER
#define WACS_LRCORNER
#define WACS_RTEE
#define WACS_LTEE
#define WACS_BTEE
#define WACS_TTEE
#define WACS_HLINE
#define WACS_VLINE
#define WACS_PLUS
#define WACS_S1
#define WACS_S9
#define WACS_DIAMOND
#define WACS_CKBOARD
#define WACS_DEGREE
#define WACS_PLMINUS
#define WACS_BULLET
#define WACS_LARROW
#define WACS_RARROW
#define WACS_DARROW
#define WACS_UARROW
#define WACS_BOARD
#define WACS_LANTERN
#define WACS_BLOCK

#define COLOR_BLACK
#define COLOR_BLUE
#define COLOR_GREEN
#define COLOR_CYAN
#define COLOR_RED
#define COLOR_MAGENTA
#define COLOR_YELLOW
#define COLOR_WHITE

#define COLOR_PAIR(x)
#define PAIR_NUMBER(x)

#define getyx(win, y, x)
#define getbegyx(win, y, x)
#define getmaxyx(win, y, x)
#define getparyx(win, y, x)

#endif /* __CURSES_H__ */
#endif
