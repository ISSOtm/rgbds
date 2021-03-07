
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "asm/string.h"

#include "helpers.h"

// A ref-counted string
struct String {
	// I hate having to use `int` there, but it's necessary to be able to print these
	size_t refs;
	int capacity;
	int len;
	char chars[];
};

int str_Len(struct String const *str)
{
	return str->len;
}

void str_Trunc(struct String *str, int len)
{
	assert(len <= str->len);

	str->len = len;
}

char str_Index(struct String const *str, int i)
{
	return str->chars[i];
}

bool str_Find(struct String const *str, char c)
{
	for (int i = 0; i < str->len; i++) {
		if (str->chars[i] == c)
			return true;
	}

	return false;
}

char const *str_Chars(struct String const *str)
{
	return str->chars;
}

struct String *str_New(int capacity)
{
	int capacity = capacity ? capacity : 32;
	struct String *str = malloc(sizeof(*str) + capacity);

	if (!str)
		return NULL;

	str->refs = 1;
	str->capacity = capacity;
	str->len = 0;
	return str;
}

void str_Ref(struct String *str)
{
	assert(str->refs != SIZE_MAX);

	str->refs++;
}

void str_Unref(struct String *str)
{
	str->refs--;
	if (!str->refs)
		free(str);
}

static bool doubleCapacity(struct String *str) warn_unused_result_
{
	static_assert(INT_MAX <= SIZE_MAX - sizeof(*str));

	if (str->capacity == INT_MAX) {
		errno = ERANGE;
		return false;

	} else if (str->capacity > (INT_MAX) / 2) {
		str->capacity = INT_MAX;
	} else {
		str->capacity *= 2;
	}

	return true;
}

struct String *str_Push(struct String *str, char c)
{
	assert(str->len <= str->capacity);

	if (str->len == str->capacity) {
		if (!doubleCapacity(str))
			return NULL;
		str = realloc(str, str->capacity);
		if (!str)
			return NULL;
	}

	str->chars[str->len++] = c;
	return str;
}

struct String *str_Append(struct String *lhs, struct String const *rhs)
{
	assert(lhs->len <= lhs->capacity);

	// Avoid overflow
	if (lhs->len > INT_MAX - rhs->len) {
		errno = ERANGE;
		return NULL;
	}

	// If the combined len is larger than the capacity, grow lhs
	if (lhs->len + rhs->len > lhs->capacity) {
		if (!doubleCapacity(lhs))
			return NULL;
		if (lhs->capacity < lhs->len)
			lhs->capacity = lhs->len;
		lhs = realloc(lhs, lhs->capacity);
		if (!lhs)
			return NULL;
	}

	// Copy chars
	memcpy(&lhs->chars[lhs->len], rhs->chars, rhs->len);
	lhs->len += rhs->len;

	return lhs;
}

void str_TrimEnd(struct String *str)
{
	while (str->len && str->chars[str->len - 1])
		str->len--;
}
