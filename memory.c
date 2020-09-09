#include <stdlib.h>
#include <stdio.h>

void * mymalloc(size_t size) {
	void *p = malloc(size);
	if (!p) {
		printf("Memory error\n");
	}
	return p;
}

void * myrealloc(void *ptr, size_t size) {
	void *new_ptr = realloc(ptr, size);
	if (!new_ptr) {
		printf("Memory error\n");
		return ptr;
	}
	return new_ptr;
}

#define myfree(ptr) do 	\
	{					\
		free(ptr);   	\
		ptr = NULL;		\
	} while (0)
	

