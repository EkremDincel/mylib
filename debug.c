#include <stdio.h>
#include <stdlib.h>

void _assert(int x, const char* msg, const char* file, int line) {
	#ifndef MY_LIB_RELEASE_MODE
		if (!x) {
			printf("\x1B[31m" "Runtime Error <%s:%i>: " "\x1B[0m" "%s\n", file, line, msg);
		}
		
	#endif

	#ifdef MY_LIB_EXIT_ON_ASSERTION
		fflush(stdout);
		exit(0);
	#endif
}

#define assert_msg(x, msg) _assert(x, msg, __FILE__, __LINE__)
#define assert(x) _assert(x, "no information.", __FILE__, __LINE__)

#define assert_not_msg(x, msg) _assert(x, msg, __FILE__, __LINE__)
#define assert_not(x) _assert(!(x), "no information.", __FILE__, __LINE__)