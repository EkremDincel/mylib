#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.c"
#include "debug.c"

typedef unsigned int uint;

typedef struct vector {
	uint lenght;
	uint capacity;
	char *array;
	uint size;
} Vector;

void vector_init(Vector *v, int size, int capacity) {
	v->lenght = 0;
	v->capacity = capacity;
	v->size = size;
	v->array = mymalloc(size * capacity);
}

void vector_resize(Vector *v, int capacity) {
	v->capacity = capacity;
	v->array = myrealloc(v->array, v->size * capacity);
}

void vector_add(Vector *v, void *value) {
	v->lenght++;
	if (v->lenght > v->capacity) {
		vector_resize(v, v->capacity * 2);
	}
	memcpy(&v->array[v->lenght * v->size], value, v->size);
}

void * vector_get(Vector *v, int index) {
	assert_not(index > v->lenght, "index is out of bounds");
	return &v->array[v->lenght * v->size];
}

void * vector_set(Vector *v, int index, void *value) {
	assert_not(index > v->lenght, "index is out of bounds");
	memcpy(&v->array[v->lenght * v->size], value, v->size);
}

void * vector_print(Vector *v, char format) {
	putchar('{');
	for (int i = 0; i < v->lenght; ++i)
	{
		printf("%" format ", ", i * v->size);
	}
	putchar('}');
	putchar('\n');
}

int main(void) {
	Vector v;
	vector_init(&v, sizeof(int), 2);
	int a = 1;
	vector_add(&v, &a);
}
