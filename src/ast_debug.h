/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#ifndef AST_DEBUG_H_
#define AST_DEBUG_H_

#include <stddef.h>
#include <stdio.h>

#include "ast.h"

#ifndef NDEBUG
void debug_ast_print_exit_node(struct ast_node *node, size_t indent);
void debug_ast_print_int_lit_node(struct ast_node *node, size_t indent);

#endif /* NDEBUG */
#endif /* AST_DEBUG_H_ */
