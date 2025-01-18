#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>

#include <errno.h>

void ignore_handler_s(const char * restrict msg, void * restrict ptr, errno_t error)
{
	errno = error;
	return;
}
