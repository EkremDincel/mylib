#include "memory.c"

static const int init_size = 2;
static const int size_multiplier = 2;

#define __vector_size_type int

#define vector_init(v) vector_from_capacity((v), init_size)

#define vector_from_capacity(v, n) 																						  	  \
	do 																														  \
	{                                                                                                                         \
		size_t *vector = mymalloc( sizeof(size_t) * 2 + (sizeof(*(v)) * (n)) );			                                      \
		(v) = (void *)(&vector[2]);																                              \
		vector_length(v) = 0;                                                                                                 \
		vector_capacity(v) = (n);																				              \
	} while (0)

#define vector_length(v)		(((size_t *)(v))[-2])
#define vector_capacity(v)		(((size_t *)(v))[-1])

#define vector_append(v, value)	((v)[vector_length(v)++] = (value))
#define vector_pop(v, value)	(vector_length(v)--)

#define vector_last(v)			((v)[vector_length(v)-1])


#define vector_iter(v, i) \
	for (size_t __counter = 0, (i) = (v)[__counter]; __counter < vector_length(v); ++__counter, (i) = (v)[__counter])

#define vector_enumerate(v, i, e) \
	for (size_t __counter = 0, i=0, (e) = (v)[__counter]; __counter < vector_length(v); ++__counter, (i) = (v)[__counter], i=__counter)


#define vector_free(v)					\
do 										\
{										\
	free(&vector_length(v));			\
	(v) = NULL;							\
} while (0)


int main(void) {
	int *vec;
	vector_init(vec);
	vector_append(vec, 2);
	vector_append(vec, 5);
	printf("%i, %i\n", vector_length(vec), vector_capacity(vec));

	int i, j;
	vector_enumerate(vec, i, j) {
		printf("%i:%i, ", i, j);
	}
	vector_free(vec);
}	