/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */

#include "ast_debug.h"

#include <stddef.h>
#include <stdio.h>

#include "ast.h"

#ifndef NDEBUG
void debug_ast_print_exit_node(struct ast_node *node, size_t indent)
{
	size_t _i;
	if (node->type != AST_NODE_TYPE_EXIT) return;

	for (_i = 0; _i < indent; _i++)
		printf("\t");

	printf("\\_Exit Statement Node with expr - \n");

	if (node->print == NULL) {
		printf("Unavailable print statment\n");
	} else {
		node->data.exit.expr->print(node->data.exit.expr, indent + 1);
	}
}

void debug_ast_print_int_lit_node(struct ast_node *node, size_t indent)
{
	size_t _i;
	if (node->type != AST_NODE_TYPE_INT_LITERAL) return;

	for (_i = 0; _i < indent; _i++)
		printf("\t");

	printf("\\_Int Literal Node with value: %d\n", node->data.int_literal);
}

#endif /* NDEBUG */
