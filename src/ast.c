/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#include "ast.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "ast_debug.h"
#include "darray.h"
#include "tokeniser.h"

static struct ast_node *parse_exit(size_t *tkn_idx, const struct prgm_tkns *tkns,
				   struct arena *arena);
static struct ast_node *parse_expr(size_t *tkn_idx, const struct prgm_tkns *tkns,
				   struct arena *arena);

int ast_create_ast(struct ast *out, const struct prgm_tkns *tkns)
{
	size_t _i;
	struct token cur_tkn;
	struct ast_node *cur_node;

	darray_create(1, sizeof(struct ast_node ), &out->ast_nodes);

	for (_i = 0; _i < tkns->token_arr.element_count; _i++) {
		if (darray_retrieve_element(_i, &tkns->token_arr, &cur_tkn) !=
		    0)
			exit(EXIT_FAILURE);

		if (cur_tkn.type == TOKEN_EXIT) {
			cur_node = parse_exit(&_i, tkns, out->arena);
			if (cur_node->type == AST_NODE_NONE)
				fprintf(stderr,
					"ERROR: parsing exit statement failed, "
					"please check syntax\n");
			darray_push(cur_node, &out->ast_nodes);
		}
	}

	return 0;
}

static struct ast_node *parse_exit(size_t *tkn_idx, const struct prgm_tkns *tkns,
				   struct arena *arena)
{
	struct token cur_tkn;
	struct ast_node *ret = NULL;

	ret = arena_alloc(arena, sizeof(struct ast_node));

	(*tkn_idx)++;
	if (darray_retrieve_element(*tkn_idx, &tkns->token_arr, &cur_tkn))
		return ret;
	if (cur_tkn.type != TOKEN_L_PAREN) return ret;

	(*tkn_idx)++;
	if (darray_retrieve_element(*tkn_idx, &tkns->token_arr, &cur_tkn))
		return ret;
	ret->type	    = AST_NODE_TYPE_EXIT;
	ret->data.exit.expr = parse_expr(tkn_idx, tkns, arena);
	ret->ir_gen	    = NULL;
#ifndef NDEBUG
	ret->print = &debug_ast_print_exit_node;
#endif

	(*tkn_idx)++;
	if (darray_retrieve_element(*tkn_idx, &tkns->token_arr, &cur_tkn))
		return ret;
	if (cur_tkn.type != TOKEN_R_PAREN) return ret;

	(*tkn_idx)++;
	if (darray_retrieve_element(*tkn_idx, &tkns->token_arr, &cur_tkn))
		return ret;
	if (cur_tkn.type != TOKEN_SEMI) return ret;

	return ret;
}

static struct ast_node *parse_expr(size_t *tkn_idx, const struct prgm_tkns *tkns,
				   struct arena *arena)
{
	struct token cur_tkn;
	struct ast_node *ret = NULL;

	ret = arena_alloc(arena, sizeof(struct ast_node));

	if (darray_retrieve_element(*tkn_idx, &tkns->token_arr, &cur_tkn))
		return ret;
	if (cur_tkn.type == TOKEN_INT_LITERAL) {
		ret->type	      = AST_NODE_TYPE_INT_LITERAL;
		ret->ir_gen	      = NULL;
		ret->data.int_literal = atoi(cur_tkn.val);
#ifndef NDEBUG
		ret->print = &debug_ast_print_int_lit_node;
#endif
	}

	return ret;
}
