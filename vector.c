#include "memory.c"

#define T int
#define N(x) x ##_## int
#define Vector(x) Vector_##x

typedef struct N(vector) {
	int lenght;
	int capacity;
	T *array;
} N(Vector);

#define vector_init(x) vector_init_##x
void N(vector_init)(N(Vector) *v, int capacity) {
	v->lenght = 0;
	v->capacity = capacity;
	v->array = mymalloc(sizeof(T) * capacity);
}

#define vector_resize(x) vector_resize_##x
void N(vector_resize)(N(Vector) *v, int capacity) {
	v->capacity = capacity;
	v->array = myrealloc(v->array, sizeof(T) * capacity);
}

#define vector_add(x) vector_add_##x
void N(vector_add)(N(Vector) *v, T value) {
	v->lenght++;
	if (v->lenght > v->capacity) {
		vector_resize(T)(&v, v->capacity * 2);
	}
	v->array[v->lenght] = value;
}

int main(void) {
	Vector(int) v;
	vector_init(int)(&v, 2);
	vector_add(int)(&v, 5);
}
