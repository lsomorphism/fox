#include <string.h>
#include "../includes/lexer.h"
#include "../includes/token.h"
#include "../includes/keyword.h"

DEFINE_VEC(token_t, token_vec)
DEFINE_VEC(const char *, lexer_error_vec)

static char next(lexer_t *lexer) {
    if(!lexer || !lexer->program || !(*lexer->program)) {
        FATAL_ERR("Lexer", "Invalid lexer state!");
        return -1; // unreachable
    }

    if(lexer->program_cursor >= lexer->program_len) {
        FATAL_ERR("Lexer","Invalid program cursor!");
    }

    char curr_char = lexer->program[lexer->program_cursor];
    lexer->program_cursor += 1;

    return curr_char;
}

static char peek_next(lexer_t *lexer) {
    if(!lexer || !lexer->program || !(*lexer->program)) {
        FATAL_ERR("Lexer", "Invalid lexer state!");
        return -1; // unreachable
    }

    if(lexer->program_cursor >= lexer->program_len && 
       lexer->program_cursor + 1 >= lexer->program_len) {
        return -1;
    }

    // Peeking requires a clone
    const char *program_clone = lexer->program;
    return program_clone[lexer->program_cursor + 1];
}

lexer_t new_lexer(char *program, size_t program_len) {
    if(!program || !(*program)) {
        FATAL_ERR("Lexer", "Provided invalid program!");
        return (lexer_t) {}; // unreachable
    }

    token_vec tokens = {0};
    if(!token_vec_reserve(&tokens, program_len)) {
        FATAL_ERR("Lexer", "Failure to allocate space for token stream!");
        return (lexer_t) {}; // unreachable
    }

    lexer_error_vec lexer_errors = {0};
    if(!new_lexer_error_vec(&lexer_errors)) {
        FATAL_ERR("Lexer", "Failure to allocate space for lexer errors!");
        return (lexer_t) {}; // unreachable
    }

    keyword_map keyword_map = {};
    if(!make_keyword_map(&keyword_map)) {
        FATAL_ERR("Lexer", "Failure to construct keyword map!");
        return (lexer_t){};
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

lexing_result tokenize(lexer_t *lexer) {
    if(!lexer) {
        FATAL_ERR("Lexer", "Invalid lexer state!");
        return err(lexing_result, {}); // unreachable
    }

    while(lexer->program[lexer->program_cursor++]) {
        switch(lexer->program[lexer->program_cursor]) {
            // Arithmetic binary operator lexing
            case '+': lex_multi_char(lexer, TOKEN_PLUS,  (char []){'+', '='}, (token_kind_t []){TOKEN_INC, TOKEN_PLUS_ASSIGN}, 2, 2);                    break;
            case '-': lex_multi_char(lexer, TOKEN_MINUS, (char []){'-', '=', '>'}, (token_kind_t []){TOKEN_DEC, TOKEN_MINUS_ASSIGN, TOKEN_ARROW}, 3, 2); break;
            case '*': lex_multi_char(lexer, TOKEN_STAR,  (char []){'='}, (token_kind_t []){TOKEN_STAR_ASSIGN}, 1, 2);                                     break;
            case '%': lex_multi_char(lexer, TOKEN_MOD,   (char []){"="}, (token_kind_t []){TOKEN_MOD_ASSIGN}, 1, 2);                                      break;
            // Also comment handling
            case '/':

            // Assignment operators
            case '=': lex_multi_char(lexer, TOKEN_ASSIGN, (char []){'='}, (token_kind_t []){TOKEN_EQU}, 1, 2); break;
            case '>': lex_multi_char(lexer, TOKEN_GT, (char []){'>', '='}, (token_kind_t){});
        }
    }
    
    return ok(lexing_result, lexer->tokens);   
}

