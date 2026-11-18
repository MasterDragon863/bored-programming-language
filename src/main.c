/* Copyright (C) 2026, MasterDragon863 (Saad Varshani) */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "ast.h"
#include "darray.h"
#include "tokeniser.h"

void print_help(void);
int read_file(const char *fpath, char **out);

int main(int argc, char **argv)
{
	char *src_file;
	struct prgm_tkns tkns;
	struct token tkn;
	struct arena ast_arena	= {NULL, NULL};
	struct arena tkns_arena = {NULL, NULL};
	struct ast ast;
#ifndef NDEBUG
	struct ast_node node;
#endif
	size_t _i;

	tkns.arena = &tkns_arena;
	ast.arena  = &ast_arena;

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

	for (_i = 0; _i < tkns.token_arr.element_count; _i++) {
		darray_retrieve_element(_i, &tkns.token_arr, &tkn);
		printf("Token: %d (%s)\n", tkn.type, tkn.val);
	}

	ast_create_ast(&ast, &tkns);

#ifndef NDEBUG
	printf("\nProgram\n");
	for (_i = 0; _i < ast.ast_nodes.element_count; _i++) {
		darray_retrieve_element(_i, &ast.ast_nodes, &node);
		if (node.print != NULL) {
			node.print(&node, 0);
		}
	}

#endif

	darray_destroy(&tkns.token_arr);
	darray_destroy(&ast.ast_nodes);

	arena_free(&tkns_arena);
	arena_free(&ast_arena);

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
