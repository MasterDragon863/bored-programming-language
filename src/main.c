/* Copyright (C) 2026, MasterDragon863 (Saad Varshani) */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "tokeniser.h"
#include "darray.h"

void print_help(void);
int read_file(const char *fpath, char **out);

int main(int argc, char **argv)
{
	char *src_file;
	struct prgm_tkns tkns;
	struct token tkn;
	size_t _i;

	if (argc < 2) {
		printf(
		    "ERROR: not enough arguments, recieved %d, expected "
		    "atleast 1",
		    argc - 1);
		print_help();
		return EXIT_FAILURE;
	}

	printf("Compiling file: %s\n", argv[1]);
	if (read_file(argv[1], &src_file) != 0) {
		printf("ERROR: Failed to read file");
		return EXIT_FAILURE;
	}
	printf("%s", src_file);

	tokenise_program(&tkns, src_file);
	free(src_file);

	for (_i = 0; _i < tkns.total_tokens; _i++)
	{

		darray_retrieve_element(_i, &tkns.token_arr, &tkn);
		printf("Token: %d (%s)\n", tkn.type, tkn.val);
	}


	return EXIT_SUCCESS;
}

void print_help(void)
{
	printf(
	    "Current usage of the compiler: \n"
	    "bored <input_file>\n");
}

int read_file(const char *fpath, char **out)
{
	FILE *file;
	size_t fsize;
	size_t ptr;
	char c;

	file = fopen(fpath, "rb");
	if (file == NULL) {
		printf("Failed to open file: %s\n", fpath);
		return 1;
	}

	fseek(file, 0L, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	*out = malloc(fsize + 1);
	if (*out == NULL) {
		fclose(file);
		return 1;
	}

	ptr = 0;
	for (;;) {
		c = fgetc(file);
		if (c == EOF) break;
		(*out)[ptr++] = c;
	}
	(*out)[fsize] = '\0';
	fclose(file);

	return 0;
}
