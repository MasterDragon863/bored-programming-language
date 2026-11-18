/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#ifndef AST_H_
#define AST_H_

#include <stddef.h>
#include "darray.h"
#include "tokeniser.h"
#include "arena.h"

struct ast_node;

typedef int (*pfn_ir_gen)(struct ast_node*);
typedef void (*pfn_debug_print)(struct ast_node*, size_t);

enum ast_node_type {
	AST_NODE_NONE = -1,
	AST_NODE_TYPE_EXIT,
	AST_NODE_TYPE_INT_LITERAL
};

struct ast_node_exit {
	struct ast_node* expr;
};

struct ast_node {
	enum ast_node_type type;

	pfn_ir_gen ir_gen;

#ifndef NDEBUG
	pfn_debug_print print;
#endif

	union {
		struct ast_node_exit exit;
		int int_literal;
	} data;
};

struct ast {
	struct darray ast_nodes;
	struct arena* arena;
};

int ast_create_ast(struct ast *out, const struct prgm_tkns *tkns);

#endif /* AST_H_ */

