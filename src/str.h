/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#ifndef STR_C_
#define STR_C_

#include <stddef.h>

struct string {
	char *str;
	size_t sz;
};

int str_create(struct string *str, const char *val);
void str_destroy(struct string *str);
int str_append(struct string *str, const char c);

#endif /*STR_C_*/
