#ifndef FOX_LEXER_KEYWORD_H_
#define FOX_LEXER_KEYWORD_H_

#include "token.h"
#include "../../shared_utils/hashmap.h"

// Keyword hashmap construction:
DECL_HASHMAP(keyword_map, const char *, token_kind_t);
bool make_keyword_map(keyword_map *);

// Specialized functions for hashmap construction:
size_t calc_str_hash(const char *);
bool are_strs_equal(const char *, const char *);
void free_str(const char *);
void free_token(token_kind_t);

#endif

