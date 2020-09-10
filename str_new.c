#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "debug.c"
#include "memory.c"

// Alias to the type bool, just for readability.
typedef bool Success;

typedef struct string {
	// length of the string.
	int length;
	// Buffer of the string, which points to the actual char array. Note that char array is *not* null-terminated.
	char* buffer;
} String;


// Initialize the string.
void string_init(String *s) {
	s->length = 0;
	s->buffer = NULL;
}

// Free the buffer of string and make it ready to re-use.
void string_free(String *s) {
	myfree(s->buffer);
	s->length = 0;
}

// Initialize the string with char array.
void string_from_buffer(String *s, char* c) {
	s->length = strlen(c);
	s->buffer = mymalloc(s->length);
	strncpy(s->buffer, c, s->length);
}

// Initialize the string with a single char.
void string_from_char(String *s, char c) {
	s->length = 1;
	s->buffer = mymalloc(1);
	s->buffer[0] = c; 
}

// Sub string [s] into string [out], from index [start] to index [end].
// The resulting buffer of [out] is points same data as the buffer of [s], so a change in one will affect both.
// Note that if you use this function, after you call [string_free] on one of the [s] or [out], accesing any of buffers of [s] or [out] is undefined behaviour.
// If you want to copy a part of [s] into [out], use [string_sub_copy] below.
void string_sub(String *s, String *out, int start, int end) {
	assert_not_msg(start > end, "start is bigger than end");
	assert_not_msg(start < 0, "start is little than zero");
	assert_not_msg(end > s->length, "end is bigger than length of the s");
	out->buffer	= s->buffer	+ start;
	out->length = end - start;
}

// Sub string [s] into string [out], from index [start] to index [end].
// Unlike [string_sub], this function does copy the specified segment into [out], so resulting string is indepented from the source.
void string_sub_copy(String *s, String *out, int start, int end) {
	assert_not_msg(start > end, "start is bigger than end");
	assert_not_msg(start < 0, "start is little than zero");
	assert_not_msg(end > s->length, "end is bigger than length of the s");
	out->length = end - start;
	out->buffer = mymalloc(out->length);
	memcpy(out->buffer, s->buffer + start, out->length);
}


void string_put(String *s, String *in, size_t offset) { // !!! include tests
	int length;
	if (s->length < offset + in->length) {
		length = s->length - offset;
	}
	else {
		length = in->length;
	}
	memcpy(s->buffer + offset, in->buffer, length);
}

// Create a copy of [s] and save it to [out].
void string_copy(String *s, String *out) {
	out->buffer = mymalloc(s->length);
	out->length = s->length;
	memcpy(out->buffer, s->buffer, s->length);
}

// Print a string, useful for debugging purposes.
void string_print(String *s) {
	for (int i = 0; i < s->length; ++i)
	{
		putchar(s->buffer[i]);
	}
}

// Returns the char in the index [index] of [s->buffer].
char string_get(String *s, int index) {
	assert_msg(index < s->length, "index is bigger than length");
	return s->buffer[index];
}

// Sets the char in the index [index] of [s->buffer] to [value].
void string_set(String *s, int index, char value) {
	assert_msg(index < s->length, "index is bigger than length");
	s->buffer[index] = value;
}

// Returns whether both string are equal.
bool string_is_equal(String *s1, String *s2) {
	if (s1->length != s2->length) return false;

	for (int i = 0; i < s1->length; ++i)
	{
		if (s1->buffer[i] != s2->buffer[i]) return false;
	}

	return true;
}

// Returns the index of first occurrence of [c] in [s].
// If there is not a occurrence, returns [-1].
int string_index(String *s, String *c) {
	int length = s->length - c->length + 1;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < c->length; ++j)
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

// Returns whether [s] contains [c].
bool string_contains(String *s, String *c) {
	return string_index(s, c) != -1;
}

// Returns the count of occurrences of [c] in [s].
int string_count(String *s, String *c) {
	int length = s->length - c->length + 1;
	int count = 0;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < c->length; ++j)
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

// Converts the string [s] to integer and returns it.
int string_to_int(String *s, Success *ok) {
	const int base = 10; // may change in the future
	const int offset_of_zero = '0';

	int value = 0;
	int value_of_digit = integer_pow(base, s->length-1);
	for (int i = 0; i < s->length; ++i)
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

// Converts the integer [num] to string and writes it into [s].
void string_from_int(String *out, int num) {
	if (num == 0) {
		string_from_char(out, '0');
		return;
	}

	const int base = 10; // may change in the future

	const int buffer_length = 11; // sign plus max 10 numbers (which is fine for a int) 

	char buffer[buffer_length];

	int negative = 0;
	if (num < 0) {
		negative = 1;
		num *= -1;
	}

	int i = buffer_length;
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

// Write the buffer of [s] into [array] as a null-terminated string.
// [array] must have a size of at least [s->length].
void string_to_buffer(String *s, char array[]) {
	memcpy(array, s->buffer, s->length);
	array[s->length] = '\0';
}

// Concatenate to strings and write into [out].
void string_add(String *s1, String *s2, String *out) {
	int length = s1->length + s2->length;
	char *buffer = mymalloc(length);
	memcpy(buffer             , s1->buffer, s1->length);
	memcpy(buffer + s1->length, s2->buffer, s2->length);
	out->length = length;
	out->buffer = buffer;
}

// Write the buffer [s] into [out], [times] times. That is, at the end length of the [out] will be [s->length * times].
void string_repeat(String *s, String *out, int times) {
	out->length = s->length * times;
	out->buffer = mymalloc(out->length);

	char* i = out->buffer;
	char* end = i + times * s->length;
	while (i < end) {
		memcpy(i, s->buffer, s->length);
		i += s->length;
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

	char a[str.length];
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

	char a[out.length];
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
	
	char a[out.length];
	string_to_buffer(&out, a);

	assert(strcmp(a, "hello ""hello ""hello ") == 0);

	string_free(&str);
	string_free(&out);
}

void test_from_int(void) {
	String s;
	string_from_int(&s, 12);
	//string_print(&s);

	char a[s.length];
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