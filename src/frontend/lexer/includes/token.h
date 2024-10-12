#ifndef FOX_LEXER_TOKEN_H_
#define FOX_LEXER_TOKEN_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// C token kinds
typedef enum {
    // Group: Keywords
    TOKEN_AUTO,
    TOKEN_BREAK,
    TOKEN_CASE,
    TOKEN_CHAR,
    TOKEN_CONST,
    TOKEN_CONTINUE,
    TOKEN_DEFAULT,
    TOKEN_DO,
    TOKEN_DOUBLE,
    TOKEN_ELSE,
    TOKEN_ENUM,
    TOKEN_EXTERN,
    TOKEN_FLOAT,
    TOKEN_FOR,
    TOKEN_GOTO,
    TOKEN_IF,
    TOKEN_INT,
    TOKEN_LONG,
    TOKEN_REGISTER,
    TOKEN_RETURN,
    TOKEN_SHORT,
    TOKEN_SIGNED,
    TOKEN_SIZEOF,
    TOKEN_STATIC,
    TOKEN_STRUCT,
    TOKEN_SWITCH,
    TOKEN_TYPEDEF,
    TOKEN_UNION,
    TOKEN_UNSIGNED,
    TOKEN_VOID,
    TOKEN_VOLATILE,
    TOKEN_WHILE,

    // Group: Arithmetic Operators
    TOKEN_PLUS,  // +
    TOKEN_MINUS, // -
    TOKEN_STAR,  // *
    TOKEN_SLASH, // /
    TOKEN_MOD,   // %

    // Group: Unary Arithmetic Operators
    TOKEN_INC, // ++
    TOKEN_DEC, // --

    // Group: Assignment Operators
    TOKEN_ASSIGN,       // =
    TOKEN_PLUS_ASSIGN,  // +=
    TOKEN_MINUS_ASSIGN, // -=
    TOKEN_STAR_ASSIGN,  // *=
    TOKEN_SLASH_ASSIGN, // /=
    TOKEN_MOD_ASSIGN,   // %=

    // Group: Comparison Operators
    TOKEN_EQU,  // ==  
    TOKEN_NEQU, // !=
    TOKEN_LT,   // <
    TOKEN_LTE,  // <=
    TOKEN_GT,   // >
    TOKEN_GTE,  // >=

    // Group: Logical Operators
    TOKEN_AND, // &&
    TOKEN_OR,  // ||
    TOKEN_NOT, // !

    // Group: Bitwise Operators
    TOKEN_RSHIFT,  // >>
    TOKEN_LSHIFT,  // <<
    TOKEN_BIT_AND, // &
    TOKEN_BIT_OR,  // | 
    TOKEN_BIT_NOT, // ~
    TOKEN_BIT_XOR, // ^

    // Group: Bitwise Assignment Operators
    TOKEN_AND_ASSIGN,    // &=
    TOKEN_OR_ASSIGN,     // |=
    TOKEN_RSHIFT_ASSIGN, // >>=
    TOKEN_LSHIFT_ASSIGN, // <<=
    TOKEN_XOR_ASSIGN,    // ^=

    // Group: Structure Access
    TOKEN_ARROW, // -> (Arrow operator)
    TOKEN_DOT,   // .

    // Group: Ternary operator
    TOKEN_QMARK, // ?
    TOKEN_COLON, // :

    // Group: Delimiters
    TOKEN_SEMICOLON,     // ;
    TOKEN_COMMA,         // ,
    TOKEN_OPEN_PAREN,    // (
    TOKEN_CLOSE_PAREN,   // )
    TOKEN_OPEN_BRACE,    // {
    TOKEN_CLOSE_BRACE,   // }
    TOKEN_OPEN_BRACKET,  // [
    TOKEN_CLOSE_BRACKET, // ]

    // Group: Literals
    TOKEN_INT_LIT,   // e.g., 42
    TOKEN_HEX_LIT,   // e.g., 0x1A
    TOKEN_FLOAT_LIT, // e.g., 3.14
    TOKEN_CHAR_LIT,  // e.g., 'a'
    TOKEN_STR_LIT,   // e.g., "hello"

    // Group: Identifiers
    TOKEN_IDENT, // Variable or function names

    // Group: Special Tokens
    TOKEN_EOF, // End of File
} token_kind_t;

typedef struct {
    size_t start, end;
} span_t;

// Token representation, contains lexeme + token kind
typedef struct {
    token_kind_t kind;
    span_t lexeme;
} token_t;

// Stringification of kind for logging
const char *kind_to_str(token_kind_t);

// Comparer function for tokens
bool are_tokens_equal(token_t, token_t);

// Print token function
void print_token(token_t);

#endif

