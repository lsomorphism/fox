#include <stdlib.h>
#include <string.h>
#include "../includes/lexer.h"
#include "../includes/token.h"
#include "../includes/keyword.h"

/* == Helper / preliminary functions for the lexer to use ==*/

DEFINE_VEC(token_t, token_vec)
DEFINE_VEC(const char *, lexer_error_vec)

static void next_while(lexer_t *lexer, bool (*predicate)(char)) {
    while(predicate(lexer->program[lexer->program_cursor])) {
        next_char(lexer);   
    }
}

static char next_char(lexer_t *lexer) {
    if(lexer->program_cursor >= lexer->program_len) {
        return -1;
    }

    char curr_char = lexer->program[lexer->program_cursor];
    lexer->program_cursor += 1;

    return curr_char;
}

char peek_char(lexer_t *lexer) {
    if(lexer->program_cursor >= lexer->program_len) {
        return -1;
    }

    return lexer->program[lexer->program_cursor];
}

static char peek_next_char(lexer_t *lexer) {
    if(lexer->program_cursor >= lexer->program_len && 
       lexer->program_cursor + 1 >= lexer->program_len) {
        return -1;
    }

    // Peeking requires a clone
    const char *program_clone = lexer->program;
    return program_clone[lexer->program_cursor + 1];
}

static bool next_matches(lexer_t *lexer, char next) {
    return peek_next_char(lexer) == next ? true : false;
}

// TODO: Probably isn't right, fix this
static void handle_comment(lexer_t *lexer) {
    while(peek_char(lexer) != '\n') {
        next_char(lexer);
    }
}

static void handle_multiline_comment(lexer_t *lexer) {
    while(peek_char(lexer) != '*') {
        next_char(lexer);

        if(next_char(lexer) == '/') {
            next_char(lexer);
            return;
        }
    }
}

/* == Public lexer interface == */

lexer_t new_lexer(char *program, size_t program_len) {
    if(!program || !(*program)) {
        FATAL_ERR("Lexer", "Provided invalid program!");
        return (lexer_t) {0}; // unreachable
    }

    token_vec tokens = {0};
    if(!new_token_vec_with(&tokens, program_len)) {
        FATAL_ERR("Lexer", "Failure to allocate space for token stream!");
        return (lexer_t) {0}; // unreachable
    }

    lexer_error_vec lexer_errors = {0};
    if(!new_lexer_error_vec(&lexer_errors)) {
        FATAL_ERR("Lexer", "Failure to allocate space for lexer errors!");
        return (lexer_t) {0}; // unreachable
    }

    keyword_map keyword_map = {0};
    if(!make_keyword_map(&keyword_map)) {
        FATAL_ERR("Lexer", "Failure to construct keyword map!");
        return (lexer_t){0};
    }

    return (lexer_t) {
        .program = program,
        .program_len = program_len,
        .program_cursor = 0,

        .tokens = tokens,
        .tokens_cursor = 0,

        .keyword_map = keyword_map,

        .lexer_errors = lexer_errors,
    };
}

void print_tokens(token_vec tokens) {
    for(size_t i = 0; i < tokens.vec_len; ++i) {
        print_token(tokens.vec_data[i]);
    }    
}

token_t lex_simple_multi_char(
    lexer_t *lexer, 
    token_kind_t short_kind, 
    char *long_match_chars, 
    token_kind_t *long_match_kinds, 
    size_t n_matches
) {
    size_t curr = lexer->program_cursor;
    
    char next = peek_next_char(lexer);
    if(next == -1) {
        return (token_t) {
            .kind = short_kind,
            .lexeme = (span_t) { .start = curr, .end = curr }  
        };
    }

    for(size_t i = 0; i < n_matches; ++i) {
        if(next_matches(lexer, long_match_chars[i])) {
            next_char(lexer);
            return (token_t) {
                .kind = long_match_kinds[i],
                .lexeme = (span_t) { .start = curr, .end = curr + 1 }
            };
        }
    }

    return (token_t) {
        .kind = short_kind,
        .lexeme = (span_t) { .start = curr, .end = curr }
    };
}

bool tokenize(lexer_t *lexer, token_vec *tokens) {
    if(!lexer || !tokens) {
        FATAL_ERR("Lexer", "Invalid lexer state!");
        return false;
    }

    for(; lexer->program[lexer->program_cursor]; ++lexer->program_cursor) {
        switch(lexer->program[lexer->program_cursor]) {            
            // Arithmetic binary operator lexing:
            case '+': {
                token_t token = lex_simple_multi_char(lexer, TOKEN_PLUS, (char []){'+', '='}, (token_kind_t []){TOKEN_INC, TOKEN_PLUS_ASSIGN}, 2);
                token_vec_insert(&lexer->tokens, token); 
                break;
            }

            case '-': {
                token_t token = lex_simple_multi_char(lexer, TOKEN_MINUS, (char []){'-', '='}, (token_kind_t []){TOKEN_DEC, TOKEN_MINUS_ASSIGN}, 2);
                token_vec_insert(&lexer->tokens, token);
                break;
            }

            case '*': {
                token_t token = lex_simple_multi_char(lexer, TOKEN_STAR, (char []){'='}, (token_kind_t []){TOKEN_STAR_ASSIGN}, 1);
                token_vec_insert(&lexer->tokens, token);
                break;
            }

            case '/': {
                if(next_matches(lexer, '/')) {
                    handle_comment(lexer);   
                    continue;
                }

                if(next_matches(lexer, '*')) {
                    handle_multiline_comment(lexer);
                    continue;
                }
                
                token_t token = lex_simple_multi_char(lexer, TOKEN_SLASH, (char []){'='}, (token_kind_t []){TOKEN_SLASH_ASSIGN}, 1);
                token_vec_insert(&lexer->tokens, token);
                break;
            }

            case '%': {
                token_t token = lex_simple_multi_char(lexer, TOKEN_MOD, (char []){'='}, (token_kind_t []){TOKEN_MOD_ASSIGN}, 1);
                token_vec_insert(&lexer->tokens, token);
                break;
            }
        }
    }

    // maybe an unnecessary copy due to "out" pattern here
    *tokens = lexer->tokens;
    return true;    
}

void delete_lexer(lexer_t *lexer) {}

