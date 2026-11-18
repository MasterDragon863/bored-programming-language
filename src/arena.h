/* Copyright (c) MasterDragon863 (Saad Varshani) */
#ifndef ARENA_H_
#define ARENA_H_

#include <stddef.h>

#define ARENA_DEFAULT_SZ (1024)

struct region {
	struct region *next;
	size_t sz;
	size_t count;
	char *data;
};

struct arena {
	struct region *start;
	struct region *end;
};

void *arena_alloc(struct arena *a, size_t sz);
void *arena_realloc(struct arena *a, void *ptr, size_t old, size_t new);
void arena_reset(struct arena *a);
void arena_free(struct arena *a);

#endif /* ARENA_H_ */
