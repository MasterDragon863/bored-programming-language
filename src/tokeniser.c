/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#include "tokeniser.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "darray.h"
#include "str.h"

static struct token retrieve_token(struct string str);
static size_t parse_token(struct token *tok, const char *prgm_str, size_t off);

int tokenise_program(struct prgm_tkns *out, const char *prgm_str)
{
	char c;
	size_t c_ptr	   = 0;
	struct token cur_tkn;
	struct darray tokens;
	struct prgm_tkns prgm;

	darray_create(1, sizeof(struct token), &tokens);

	for (;;) {
		c = prgm_str[c_ptr];
		if (c == '\0') break;
		switch (c) {
			case ';':
				cur_tkn.type = TOKEN_SEMI;
				darray_push(&cur_tkn, &tokens);
				c_ptr++;
				continue;
				break;
			case ')':
				cur_tkn.type = TOKEN_R_PAREN;
				darray_push(&cur_tkn, &tokens);
				c_ptr++;
				continue;
				break;
			case '(':
				cur_tkn.type = TOKEN_L_PAREN;
				darray_push(&cur_tkn, &tokens);
				c_ptr++;
				continue;
				break;
		}

		if (isalnum(c)) {
			c_ptr += parse_token(&cur_tkn, prgm_str, c_ptr);
			darray_push(&cur_tkn, &tokens);
			continue;
		}

		c_ptr++;

	}

	prgm.token_arr	  = tokens;
	prgm.total_tokens = tokens.element_count;
	*out		  = prgm;

	return 0;
}

static struct token retrieve_token(struct string str)
{
	size_t _i;
	int is_int_lit = 1;
	struct token tkn;

	tkn.type = TOKEN_NO_TOKEN;
	tkn.val	 = str.str;

	for (_i = 0; _i < str.sz; _i++) {
		if (isdigit(str.str[_i]) != 0) continue;
		is_int_lit = 0;
		break;
	}

	if (is_int_lit) tkn.type = TOKEN_INT_LITERAL;

	if (strcmp(str.str, "ext") == 0) tkn.type = TOKEN_EXIT;
	if (strcmp(str.str, ";") == 0) tkn.type = TOKEN_SEMI;

	return tkn;
}

static size_t parse_token(struct token *tok, const char *prgm_str,
			  const size_t off)
{
	char c;
	size_t c_ptr	  = off;
	struct string buf = {NULL, 0};
	for (;;) {
		c = prgm_str[c_ptr];
		if (c == '\0') {
			if (buf.str == NULL) break;
			*tok = retrieve_token(buf);
			break;
		}

		if (buf.str == NULL) {
			str_create(&buf, "");
		}

		if (c == ';' || c == '(' || c == ')' || c == ' ') {
			*tok = retrieve_token(buf);
			break;
		}

		if (isalnum(c)) {
			if (str_append(&buf, c) != 0) {
				printf("buf is NULL: %d\n", buf.str == NULL);
				printf("ERROR: in parse_token, failed to append c\n");
				exit(EXIT_FAILURE);
			}
		}

		c_ptr++;
	}

	return c_ptr - off;
}
