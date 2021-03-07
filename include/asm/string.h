/*
 * This file is part of RGBDS.
 *
 * Copyright (c) 2021, Eldred Habert and RGBDS contributors.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RGBDS_STRING_H
#define RGBDS_STRING_H

#include <stdbool.h>

#include "helpers.h"

struct String;

#define PRI_STR ".*s"
// WARNING: **DO NOT** pass any side-effecting parameters to the macro below!!
#define STR_FMT(str) str_Len(str), str_Chars(str)

static inline bool str_IsWhitespace(int c)
{
	return c == ' ' || c == '\t';
}

int str_Len(struct String const *str) pure_;
void str_Trunc(struct String *str, int len);
char str_Index(struct String const *str, int i) pure_;
bool str_Find(struct String const *str, char c) pure_;
char const *str_Chars(struct String const *str) pure_;

/**
 * @param capacity The capacity to use, or 0 if unknown
 */
struct String *str_New(int capacity) mallocish_;
void str_Ref(struct String *str);
void str_Unref(struct String *str);

struct String *str_Push(struct String *str, char c) warn_unused_result_;
struct String *str_Append(struct String *lhs, struct String const *rhs) warn_unused_result_;
struct String *str_AppendSlice(struct String *lhs, char const *rhs, int len) warn_unused_result_;
void str_TrimEnd(struct String *str);

#endif
