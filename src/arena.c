/* Copyright (c) MasterDragon863 (Saad Varshani) */
#include "arena.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct region *region_create(size_t sz);

void *arena_alloc(struct arena *a, size_t sz)
{
	struct region *new_rgn;
	void *ret = NULL;

	if (a->start == NULL) {
		new_rgn	 = region_create(ARENA_DEFAULT_SZ);
		a->start = new_rgn;
		a->end	 = new_rgn;
	}

	for (;;) {
		if (a->end->next == NULL) break;
		if (a->end->count + sz < a->end->sz) break;

		a->end = a->end->next;
	}

	if (a->end->count + sz > a->end->sz) {
		new_rgn	       = region_create(sz);
		a->start->next = new_rgn;
		a->end	       = new_rgn;
	}

	ret = &a->end->data[a->end->count];
	a->end->count += sz;
	return ret;
}

void *arena_realloc(struct arena *a, void *ptr, size_t old, size_t new)
{
	void *newptr = NULL;
	if (old >= new) return ptr;

	newptr = arena_alloc(a, new);
	memcpy(newptr, ptr, old);

	return newptr;
}

void arena_reset(struct arena *a)
{
	struct region *reg;

	reg = a->start;
	for (;;) {
		reg = reg->next;
		if (reg == NULL) break;
		reg->count = 0;
	}

	a->end = a->start;
}

void arena_free(struct arena *a)
{
	struct region *r;
	struct region *r_nxt;

	r_nxt = a->start;
	for (;;) {
		if (r_nxt == NULL) break;
		r     = r_nxt;
		r_nxt = r->next;
		free(r->data);
		free(r);
	}

	a->start = NULL;
	a->end	 = NULL;
}

static struct region *region_create(size_t sz)
{
	struct region *region;

	region	      = malloc(sizeof(struct region));
	region->next  = NULL;
	region->sz    = sz;
	region->count = 0;
	region->data  = malloc(sz);

	return region;
}
