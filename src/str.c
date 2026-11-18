/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */

#include "str.h"

#include <string.h>
#include "arena.h"

int str_create(struct string *str, const char *val, struct arena *a)
{
	if (str == NULL) return 1;
	if (val == NULL) return 1;

	str->sz	 = strlen(val);
	str->str = arena_alloc(a, str->sz + 1);

	if (str->str == NULL) return 1;
	if (!(memcpy(str->str, val, str->sz))) {
		return 1;
	}

	return 0;
}

int str_append(struct string *str, const char c, struct arena *a)
{
	char *new;
	if (str == NULL) return 1;
	if (str->str == NULL) return 1;

	new = arena_realloc(a, str->str, str->sz, str->sz + 2);
	if (new == NULL) return 1;

	str->str	  = new;
	str->str[str->sz] = c;
	str->sz++;
	str->str[str->sz] = '\0';

	return 0;
}
