#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "debug.c"
#include "memory.c"

typedef bool Success;

typedef struct string {
	char* buffer;
	int lenght;
} String;

void string_init(String *s) {
	s->lenght = 0;
	s->buffer = NULL;
}

void string_free(String *s) {
	myfree(s->buffer);
	s->lenght = 0;
}

void string_from_buffer(String *s, char* c) {
	s->lenght = strlen(c);
	s->buffer = mymalloc(s->lenght);
	strncpy(s->buffer, c, s->lenght);
}

void string_from_char(String *s, char c) {
	s->lenght = 1;
	s->buffer = mymalloc(1);
	s->buffer[0] = c; 
}

void string_sub(String *s, String *out, int start, int end) {
	assert_not_msg(start > end, "start is bigger than end");
	assert_not_msg(start < 0, "start is little than zero");
	assert_not_msg(end > s->lenght, "end is bigger than lenght of the s");
	out->buffer	= s->buffer	+ start;
	out->lenght = end - start;
}

void string_sub_copy(String *s, String *out, int start, int end) {
	assert_not_msg(start > end, "start is bigger than end");
	assert_not_msg(start < 0, "start is little than zero");
	assert_not_msg(end > s->lenght, "end is bigger than lenght of the s");
	out->lenght = end - start;
	out->buffer = mymalloc(out->lenght);
	memcpy(out->buffer, s->buffer + start, out->lenght);
}

void string_put(String *s, String *in, size_t offset) {
	int lenght;
	if (s->lenght < offset + in->lenght) {
		lenght = s->lenght - offset;
	}
	else {
		lenght = in->lenght;
	}
	memcpy(s->buffer + offset, in->buffer, lenght);
}

void string_copy(String *s, String *out) {
	out->buffer = mymalloc(s->lenght);
	out->lenght = s->lenght;
	memcpy(out->buffer, s->buffer, s->lenght);
}

void string_print(String *s) {
	for (int i = 0; i < s->lenght; ++i)
	{
		putchar(s->buffer[i]);
	}
}

char string_get(String *s, int index) {
	assert_msg(index < s->lenght, "index is bigger than lenght");
	return s->buffer[index];
}

void string_set(String *s, int index, char value) {
	assert_msg(index < s->lenght, "index is bigger than lenght");
	s->buffer[index] = value;
}

bool string_is_equal(String *s1, String *s2) {
	if (s1->lenght != s2->lenght) return false;

	for (int i = 0; i < s1->lenght; ++i)
	{
		if (s1->buffer[i] != s2->buffer[i]) return false;
	}

	return true;
}

int string_index(String *s, String *c) {
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
	return string_index(s, c) != -1;
}

int string_count(String *s, String *c) {
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
	const int offset_of_zero = '0';

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

void string_from_int(String *out, int num) {
	if (num == 0) {
		string_from_char(out, '0');
		return;
	}

	const int base = 10; // may change in the future

	const int buffer_lenght = 11; // sign plus max 10 numbers (which is fine for a int) 

	char buffer[buffer_lenght];

	int negative = 0;
	if (num < 0) {
		negative = 1;
		num *= -1;
	}

	int i = buffer_lenght;
	while (num)
	{
		buffer[i] = "0123456789"[num % base];
		num /= base;
		i--;
	}
	
	if (negative) buffer[i--] = '-';
	//printf("%s\n", &buffer[i+1]);
	string_from_buffer(out, &buffer[i+1]);
}

void string_to_buffer(String *s, char array[]) {
	memcpy(array, s->buffer, s->lenght);
	array[s->lenght] = '\0';
}

void string_add(String *s1, String *s2, String *out) {
	int lenght = s1->lenght + s2->lenght;
	char *buffer = mymalloc(lenght);
	memcpy(buffer             , s1->buffer, s1->lenght);
	memcpy(buffer + s1->lenght, s2->buffer, s2->lenght);
	out->lenght = lenght;
	out->buffer = buffer;
}

void string_repeat(String *s, String *out, int times) {
	out->lenght = s->lenght * times;
	out->buffer = mymalloc(out->lenght);

	char* i = out->buffer;
	char* end = i + times * s->lenght;
	while (i < end) {
		memcpy(i, s->buffer, s->lenght);
		i += s->lenght;
	}
}

void string_join(String *s) {

}

void string_reverse(String *s, String *out) {

}


#define MY_TEST
#ifdef MY_TEST

void test_add(void); 
void test_to_int(void); 
void test_repeat(void);
void test_to_buffer(void);
void test_equal(void);
void test_copy(void);
void test_from_int(void);

int main(void) {
	test_equal();
	test_to_buffer();
	test_add();
	test_repeat();
	test_to_int();
	test_from_int();
	test_copy();
}

void test_equal(void) {
	char *buffer = "hello world.";
 
	String str;
	string_from_buffer(&str, buffer);

	String another;
	string_from_buffer(&another, buffer);

	assert(string_is_equal(&str, &another));

	string_free(&another);
	string_from_buffer(&another, "hellA world.");

	assert_not(string_is_equal(&str, &another));

	string_free(&str);
	string_free(&another);
}

void test_to_buffer(void) {
	char *buffer = "hello world.";

	String str;
	string_from_buffer(&str, buffer);

	char a[str.lenght];
	string_to_buffer(&str, a);
	
	assert(strcmp(a, buffer) == 0);

	string_free(&str);
}

void test_add(void) {
	String str;
	String str2;
	string_from_buffer(&str, "hello ");
	string_from_buffer(&str2, "world!");

	String out;
	string_add(&str, &str2, &out);

	char a[out.lenght];
	string_to_buffer(&out, a);
	assert(strcmp(a, "hello world!") == 0);

	string_free(&str);
	string_free(&str2);
	string_free(&out);
}

void test_repeat(void) {
	String str;
	string_from_buffer(&str, "hello ");

	String out;
	string_repeat(&str, &out, 3);
	
	char a[out.lenght];
	string_to_buffer(&out, a);

	assert(strcmp(a, "hello ""hello ""hello ") == 0);

	string_free(&str);
	string_free(&out);
}

void test_from_int(void) {
	String s;
	string_from_int(&s, 12);
	//string_print(&s);

	char a[s.lenght];
	string_to_buffer(&s, a);

	assert(strcmp(a, "12") == 0);

	string_free(&s);
}

void test_to_int(void) {
	String str;
	string_from_buffer(&str, "12a");

	Success ok;
	int num = string_to_int(&str, &ok);

	assert_not(ok);
	assert(num == 120);

	string_free(&str);

	string_from_buffer(&str, "34590");
	num = string_to_int(&str, &ok);

	assert(ok);
	assert(num == 34590);

	string_free(&str);
}


void test_copy(void) {
	String str;
	string_from_buffer(&str, "hello world.");

	String another;
	string_copy(&str, &another);
	assert(string_is_equal(&str, &another));

	string_free(&str);
	string_free(&another);
}

#endif