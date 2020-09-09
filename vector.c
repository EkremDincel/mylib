#define T int
#define N(x) x_##int
#define Vector(x) Vector_##x

typedef struct N(vector) {
	int lenght;
	int capacity;
	T *array;
} N(Vector);

#define vector_init(x) vector_init_##x
void N(vector_init)(Vector *v) {
	v->lenght = 0;
	v->capacity = 2;
	v->array = malloc(sizeof(T) * self.capacity);
}