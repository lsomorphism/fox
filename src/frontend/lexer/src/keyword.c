#include <string.h>
#include "../includes/keyword.h"
#include "../../shared_utils/logger.h"

#define FNV_PRIME 0x100000001b3ul
#define FNV_OFFSET_BASIS 0xcbf29ce484222325ul

size_t calc_str_hash(const char *key) {
    size_t hash = FNV_OFFSET_BASIS;

    for(; *key; ++key) {
        hash ^= *key;
        hash *= FNV_PRIME; 
    }

    return hash;
}

bool are_strs_equal(const char *key_1, const char *key_2) {
    if(!key_1 || !key_2) {
        return false;
    }

    if(strlen(key_1) != strlen(key_2)) {
        return false;
    }
    
    return !strcmp(key_1, key_2);
}

// neither are dynamically allocated
void free_str(const char * _) {}
void free_token(token_kind_t _) {}

DEFINE_HASHMAP(keyword_map, const char *, token_kind_t, calc_str_hash, are_strs_equal, free_str, free_token)

bool make_keyword_map(keyword_map *keyword_mapping) {
    // No static hashmap :( (yet)
    if(!keyword_mapping || !keyword_map_reserve(keyword_mapping, 32)) {
        FATAL_ERR("Lexer", "Invalid keyword hashmap state!");
        return false; // unreachable
    }

    keyword_map_insert(keyword_mapping, "auto",     TOKEN_AUTO);
    keyword_map_insert(keyword_mapping, "break",    TOKEN_BREAK);
    keyword_map_insert(keyword_mapping, "case",     TOKEN_CASE);
    keyword_map_insert(keyword_mapping, "char",     TOKEN_CHAR);
    keyword_map_insert(keyword_mapping, "const",    TOKEN_CONST);
    keyword_map_insert(keyword_mapping, "continue", TOKEN_CONTINUE);
    keyword_map_insert(keyword_mapping, "default",  TOKEN_DEFAULT);
    keyword_map_insert(keyword_mapping, "do",       TOKEN_DO);
    keyword_map_insert(keyword_mapping, "double",   TOKEN_DOUBLE);
    keyword_map_insert(keyword_mapping, "else",     TOKEN_ELSE);
    keyword_map_insert(keyword_mapping, "enum",     TOKEN_ENUM);
    keyword_map_insert(keyword_mapping, "extern",   TOKEN_EXTERN);
    keyword_map_insert(keyword_mapping, "float",    TOKEN_FLOAT);
    keyword_map_insert(keyword_mapping, "for",      TOKEN_FOR);
    keyword_map_insert(keyword_mapping, "goto",     TOKEN_GOTO);
    keyword_map_insert(keyword_mapping, "if",       TOKEN_IF);
    keyword_map_insert(keyword_mapping, "int",      TOKEN_INT);
    keyword_map_insert(keyword_mapping, "long",     TOKEN_LONG);
    keyword_map_insert(keyword_mapping, "register", TOKEN_REGISTER);
    keyword_map_insert(keyword_mapping, "return",   TOKEN_RETURN);
    keyword_map_insert(keyword_mapping, "short",    TOKEN_SHORT);
    keyword_map_insert(keyword_mapping, "signed",   TOKEN_SIGNED);
    keyword_map_insert(keyword_mapping, "sizeof",   TOKEN_SIZEOF);
    keyword_map_insert(keyword_mapping, "static",   TOKEN_STATIC);
    keyword_map_insert(keyword_mapping, "struct",   TOKEN_STRUCT);
    keyword_map_insert(keyword_mapping, "switch",   TOKEN_SWITCH);
    keyword_map_insert(keyword_mapping, "typedef",  TOKEN_TYPEDEF);
    keyword_map_insert(keyword_mapping, "union",    TOKEN_UNION);
    keyword_map_insert(keyword_mapping, "unsigned", TOKEN_UNSIGNED);
    keyword_map_insert(keyword_mapping, "void",     TOKEN_VOID);
    keyword_map_insert(keyword_mapping, "volatile", TOKEN_VOLATILE);
    keyword_map_insert(keyword_mapping, "while",    TOKEN_WHILE);
    
    return true;
}

