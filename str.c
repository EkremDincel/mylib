#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "debug.c"

typedef bool Success;

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
	int lenght = s->lenght - c->lenght + 1;
	for (int i = 0; i < lenght; ++i)
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
	int lenght = s->lenght - c->lenght + 1;
	int count = 0;
	for (int i = 0; i < lenght; ++i)
	{
		for (int j = 0; j < c->lenght; ++j)
		{
			if (s->buffer[i+j] != c->buffer[j]) {
				goto string_index_of_double_continue;
			}
		}
		count++;

string_index_of_double_continue:;
	}
	return count;
}

static int integer_pow(int i, int j) {
	int value = 1;
	for (int k = 0; k < j; ++k)
	{
		value *= i;
	}
	return value;
}

int string_to_int(String *s, Success *ok) {
	const int base = 10; // may change in the future
	const int offset_of_zero = 48;

	int value = 0;
	int value_of_digit = integer_pow(base, s->lenght-1);
	for (int i = 0; i < s->lenght; ++i)
	{
		int number = s->buffer[i] - offset_of_zero;
		if (!(number < base) || number < 0) {
			*ok = false;
			return value;
		}
		value += number * value_of_digit;
		value_of_digit /= base;
	}
	*ok = true;
	return value;
}

void string_from_int(String *out, int number) {

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
	string_from_buffer(&str, "12a");

	Success ok;
	printf("number: %i, success: %i\n", string_to_int(&str, &ok), ok);

}