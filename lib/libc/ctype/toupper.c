#include <ctype.h>

int toupper(int c)
{
    if (c >= 'a' && c <= 'z') return c + ('A' - 'a');
    return c;
}
