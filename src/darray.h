/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <stddef.h>

struct darray {
	void *data;
	size_t element_size;
	size_t allocated_size;
	size_t element_count;
};

int darray_create(size_t element_count, size_t element_size,
		  struct darray *arr);
int darray_push(void  *element, struct darray *arr);
int darray_retrieve_element(size_t idx, const struct darray *arr,
			    void *out);
int darray_pop(struct darray *arr, void *out);
int darray_remove(size_t idx, struct darray *arr, void *out);
void darray_destroy(struct darray *arr);

#endif
