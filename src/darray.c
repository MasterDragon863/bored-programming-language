/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#include "darray.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int darray_create(size_t element_count, size_t element_size, struct darray *arr)
{
	assert(element_count > 0);
	assert(element_size > 0);
	assert(arr != NULL);

	arr->element_size   = element_size;
	arr->allocated_size = element_count * element_size;
	arr->element_count  = 0;
	arr->data	    = malloc(element_count * element_size);
	if (arr->data == NULL) {
		return 1;
	}

	return 0;
}

int darray_push(void *element, struct darray *arr)
{
	char *dest;
	if (arr->element_count * arr->element_size >= arr->allocated_size) {
		size_t new_size = arr->allocated_size * 2;
		void *new_data	= realloc(arr->data, new_size);

		if (new_data == NULL) {
			return 1;
		}

		arr->data	    = new_data;
		arr->allocated_size = new_size;
	}

	dest = (char *)arr->data + (arr->element_count * arr->element_size);

	memcpy(dest, element, arr->element_size);

	arr->element_count++;

	return 0;
}

int darray_retrieve_element(size_t idx, const struct darray *arr, void *out)
{
	char *src;
	if (idx >= arr->element_count) {
		return 1;
	}

	src = (char *)arr->data + (idx * arr->element_size);

	memcpy(out, src, arr->element_size);

	return 0;
}

int darray_pop(struct darray *arr, void *out)
{
	if (arr->element_count <= 0) return 1;

	arr->element_count--;
	if (out != NULL) {
		char *src = (char *)arr->data +
			    (arr->element_count * arr->element_size);
		memcpy(out, src, arr->element_size);
	}

	return 0;
}

int darray_remove(size_t idx, struct darray *arr, void *out)
{
	char *dest;
	char *src;
	size_t bytes_to_move;
	if (idx >= arr->element_count) return 1;

	dest = (char *)arr->data + (idx * arr->element_size);

	if (out != NULL) memcpy(out, dest, arr->element_size);

	src = (char *)arr->data + ((idx + 1) * arr->element_size);
	bytes_to_move =
	    (arr->element_count - idx - 1) * arr->element_size;

	if (bytes_to_move > 0) memmove(dest, src, bytes_to_move);

	arr->element_count--;

	return 0;
}

void darray_destroy(struct darray *arr)
{
	struct darray empty = {NULL, 0, 0, 0};
	assert(arr != NULL);

	free(arr->data);

	*arr = empty;
}
