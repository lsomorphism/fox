#ifndef FOX_LEXER_H_
#define FOX_LEXER_H_

// Standard imports
#include <stdbool.h>

// Token type import
#include "token.h"

// Keyword hashmap import
#include "keyword.h"

// Shared imports
#include "../../shared_utils/result.h"
#include "../../shared_utils/vector.h"
#include "../../shared_utils/logger.h"

DECL_VEC(token_t, token_vec)
// Note: Possible custom error type, but strings for now
DECL_VEC(const char *, lexer_error_vec)

// TODO: Add support for string interning
typedef struct {
    char *program;
    size_t program_cursor, program_len;

    token_vec tokens;
    size_t tokens_cursor;

    lexer_error_vec lexer_errors;

    keyword_map keyword_map;

    // string_interner interner;
} lexer_t;

// Lookahead functionalities:
static char next_char(lexer_t *);
static char peek_next_char(lexer_t *);

// Lexing functionailties
static token_t lex_single_char(lexer_t *, char);
static token_t lex_simple_multi_char(lexer_t *, token_kind_t, char *, token_kind_t *, size_t);

// Lexing literals
static token_t lex_int_lit(lexer_t *);

// Initialization & Deinitialization
lexer_t new_lexer(char *, size_t);
void delete_lexer(lexer_t *);

// Lexing function
bool tokenize(lexer_t *, token_vec *);

// Utility / debuggin
void print_tokens(token_vec);

#endif

