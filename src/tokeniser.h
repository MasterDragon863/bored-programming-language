/* Copyright (C) 2026 MasterDragon863 (Saad Varshani) */
#ifndef TOKENISER_H_
#define TOKENISER_H_

#include <stddef.h>
#include "darray.h"

enum token_enum {
	TOKEN_NO_TOKEN = -1,
	TOKEN_EXIT,
	TOKEN_INT_LITERAL,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN,
	TOKEN_SEMI
};

struct token {
	enum token_enum type;
	char* val;
};

struct prgm_tkns {
	struct darray token_arr;
	size_t total_tokens;
};

int tokenise_program(struct prgm_tkns *out, const char *prgm_str);

#endif /*TOKENISER_H_*/
