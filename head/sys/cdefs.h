#ifndef SYS_CDEFS_H
#define SYS_CDEFS_H
#if 0
#define precondition
#define postcondition

#define checkpoint
#define watchdog

#define ck_notnull
#define ck_bounds
#define ck_restrict

#define ft_compare
#define ft_loop_bound
#define attr_keyword attribute_name
#define __strict_weak_alias(alias, sym)
#define __compactcall
#endif

#define asm __asm__

#define PRAGMA
#define ___STRING(x) __STRING(x)
#define ___CONCAT(x,y) __CONCAT(x,y)
#define __P(protos) protos /* full-blown ANSI C */
#define __CONCAT(x,y) x ## y
#define __STRING(x) #x

#if 0
#define __P(protos) ()  /* traditional C preprocessor */
#define __CONCAT(x,y) x/**/y
#define __STRING(x) "x"
#endif


#endif /* SYS_CDEFS_H */

