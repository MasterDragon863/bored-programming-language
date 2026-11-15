/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */

#include "str.h"

#include <stdlib.h>
#include <string.h>

int str_create(struct string *str, const char *val)
{
	if (str == NULL) return 1;
	if (val == NULL) return 1;

	str->sz	 = strlen(val);
	str->str = malloc(str->sz + 1);

	if (str->str == NULL) return 1;
	if (!(memcpy(str->str, val, str->sz))) {
		free(str->str);
		return 1;
	}

	return 0;
}

void str_destroy(struct string *str)
{
	free(str->str);
	str->sz = 0;
}

int str_append(struct string *str, const char c)
{
	char *new;
	if (str == NULL) return 1;
	if (str->str == NULL) return 1;

	new = realloc(str->str, str->sz + 2);
	if (new == NULL) return 1;

	str->str	  = new;
	str->str[str->sz] = c;
	str->sz++;
	str->str[str->sz] = '\0';

	return 0;
}
