#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "debug.c"

typedef struct string {
	const char* buffer;
	int lenght;
} String;

void string_from_buffer(String *s, const char* c) {
	s->buffer = c;
	s->lenght = strlen(c);
}

void string_from_char(String *s, const char c) {
	s->buffer = &c;
	s->lenght = 1;
}

void string_sub_into(String *s, String *out, int start, int end) {
	assert_not(start > end, "start is bigger than end");
	assert_not(start < 0, "start is little than zero");
	assert_not(end > s->lenght, "end is bigger than lenght of the s");
	out->buffer	= s->buffer	+ start;
	out->lenght = end - start;
}

void string_print(String *s) {
	for (int i = 0; i < s->lenght; ++i)
	{
		putchar(s->buffer[i]);
	}
}

char string_get(String *s, int index) {
	assert(index < s->lenght, "index is bigger than lenght");
	return s->buffer[index];
}

bool string_is_equal(String *s1, String *s2) {
	if (s1->lenght != s2->lenght) return false;

	for (int i = 0; i < s1->lenght; ++i)
	{
		if (s1->buffer[i] != s2->buffer[i]) return false;
	}

	return true;
}

int string_index_of(String *s, String *c) {
	if (s->lenght < c->lenght) return -1;

	for (int i = 0; i < s->lenght; ++i)
	{
		for (int j = 0; j < c->lenght; ++j)
		{
			if (s->buffer[i+j] != c->buffer[j]) {
				goto string_index_of_double_continue;
			}
		}
		return i;

string_index_of_double_continue:;
	}
	return -1;
}

bool string_contains(String *s, String *c) {
	return string_index_of(s, c) != -1;
}

void string_foreach(String *s, void (*f)(char)) {
	for (int i = 0; i < s->lenght; ++i)
	{
		(*f)(s->buffer[i]);
	}
}

int string_count_of(String *s, String *c) {
	
}

//mutable string
typedef struct mut_string {
	char* buffer;
	int lenght;
} MutString;

void string_set(MutString *s, int index, char value) {
	assert(index < s->lenght, "index is bigger than lenght");
	s->buffer[index] = value;
}

String* string_as_unmutable(MutString *s) {
	return (String*) s;
}

MutString* string_as_mutable(String *s) {
	return (MutString*) s;
}


int main(void) {
	String str;
	string_from_buffer(&str, "ekrem");

	String another_str;
	string_from_buffer(&another_str, "z");

	printf("%i", string_index_of(&str, &another_str));
}