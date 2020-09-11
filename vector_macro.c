#include "memory.c"

static const int init_size = 2;
static const int size_multiplier = 2;

#define __vector_size_type int

#define vector_create(v) 																								  \
do 																														  \
{	/*                     ||       vector lenght 	   | 		vector capacity 	| 	vector data 		||			*/\
	/*                                                                              ^									*/\
	/*                                                                             [v] pointer							*/\
	char *vector = mymalloc(sizeof(__vector_size_type) + sizeof(__vector_size_type) + (sizeof(v) * init_size));			  \
	printf("first head %i\n", vector);\
	v = (void *)(vector + sizeof(__vector_size_type) * 2);																  \
	_vector_set_length(v, 0);																							  \
	_vector_set_capacity(v, init_size);																					  \
} while (0)

#define vector_length(v)			 (*(__vector_size_type *)(v - sizeof(__vector_size_type) * 2))
#define _vector_set_length(v, n)     (*(__vector_size_type *)(v - sizeof(__vector_size_type) * 2) = n)

#define vector_capacity(v)			 (*(__vector_size_type *)(v - sizeof(__vector_size_type)))
#define _vector_set_capacity(v, n)   (*(__vector_size_type *)(v - sizeof(__vector_size_type)) = n)

#define vector_free(v)	\
do 						\
{						\
	printf("%i, %i\n", v, (char *)v-8);\
	free(((char *)v - 8));			\
	printf("null\n");\
	v = NULL;			\
} while (0)


int main(void) {
	int *vec;
	vector_create(vec);
	printf("%i, %i\n", vec[-1], vec[-2]);
	printf("%i, %i\n", vector_length(vec), vector_capacity(vec));
	vector_free(vec);
	printf("%s\n", "finish");
}	