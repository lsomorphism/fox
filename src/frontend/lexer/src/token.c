#include <string.h>
#include "../includes/token.h"

bool are_tokens_equal(token_t a, token_t b) {
    bool equal_kinds   = a.kind == b.kind;
    bool equal_lexemes = (a.lexeme.start == b.lexeme.start) && (a.lexeme.end == b.lexeme.end);

    return equal_kinds && equal_lexemes;
}

const char *kind_to_str(token_kind_t kind) {
    switch (kind) {        // Keywords
        case TOKEN_AUTO:          return "token_auto";
        case TOKEN_BREAK:         return "token_break";
        case TOKEN_CASE:          return "token_case";
        case TOKEN_CHAR:          return "token_char";
        case TOKEN_CONST:         return "token_const";
        case TOKEN_CONTINUE:      return "token_continue";
        case TOKEN_DEFAULT:       return "token_default";
        case TOKEN_DO:            return "token_do";
        case TOKEN_DOUBLE:        return "token_double";
        case TOKEN_ELSE:          return "token_else";
        case TOKEN_ENUM:          return "token_enum";
        case TOKEN_EXTERN:        return "token_extern";
        case TOKEN_FLOAT:         return "token_float";
        case TOKEN_FOR:           return "token_for";
        case TOKEN_GOTO:          return "token_goto";
        case TOKEN_IF:            return "token_if";
        case TOKEN_INT:           return "token_int";
        case TOKEN_LONG:          return "token_long";
        case TOKEN_REGISTER:      return "token_register";
        case TOKEN_RETURN:        return "token_return";
        case TOKEN_SHORT:         return "token_short";
        case TOKEN_SIGNED:        return "token_signed";
        case TOKEN_SIZEOF:        return "token_sizeof";
        case TOKEN_STATIC:        return "token_static";
        case TOKEN_STRUCT:        return "token_struct";
        case TOKEN_SWITCH:        return "token_switch";
        case TOKEN_TYPEDEF:       return "token_typedef";
        case TOKEN_UNION:         return "token_union";
        case TOKEN_UNSIGNED:      return "token_unsigned";
        case TOKEN_VOID:          return "token_void";
        case TOKEN_VOLATILE:      return "token_volatile";
        case TOKEN_WHILE:         return "token_while";

        // Arithmetic Operators
        case TOKEN_PLUS:          return "token_plus";
        case TOKEN_MINUS:         return "token_minus";
        case TOKEN_STAR:          return "token_star";
        case TOKEN_SLASH:         return "token_slash";
        case TOKEN_MOD:           return "token_mod";

        // Unary Arithmetic Operators
        case TOKEN_INC:           return "token_inc";
        case TOKEN_DEC:           return "token_dec";

        // Assignment Operators
        case TOKEN_ASSIGN:        return "token_assign";
        case TOKEN_PLUS_ASSIGN:   return "token_plus_assign";
        case TOKEN_MINUS_ASSIGN:  return "token_minus_assign";
        case TOKEN_STAR_ASSIGN:   return "token_star_assign";
        case TOKEN_SLASH_ASSIGN:  return "token_slash_assign";
        case TOKEN_MOD_ASSIGN:    return "token_mod_assign";

        // Comparison Operators
        case TOKEN_EQU:           return "token_equ";
        case TOKEN_NEQU:          return "token_nequ";
        case TOKEN_LT:            return "token_lt";
        case TOKEN_LTE:           return "token_lte";
        case TOKEN_GT:            return "token_gt";
        case TOKEN_GTE:           return "token_gte";

        // Logical Operators
        case TOKEN_AND:           return "token_and";
        case TOKEN_OR:            return "token_or";
        case TOKEN_NOT:           return "token_not";

        // Bitwise Operators
        case TOKEN_RSHIFT:        return "token_rshift";
        case TOKEN_LSHIFT:        return "token_lshift";
        case TOKEN_BIT_AND:       return "token_bit_and";
        case TOKEN_BIT_OR:        return "token_bit_or";
        case TOKEN_BIT_NOT:       return "token_bit_not";
        case TOKEN_BIT_XOR:       return "token_bit_xor";

        // Bitwise Assignment Operators
        case TOKEN_AND_ASSIGN:    return "token_and_assign";
        case TOKEN_OR_ASSIGN:     return "token_or_assign";
        case TOKEN_RSHIFT_ASSIGN: return "token_rshift_assign";
        case TOKEN_LSHIFT_ASSIGN: return "token_lshift_assign";
        case TOKEN_XOR_ASSIGN:    return "token_xor_assign";

        // Structure Access
        case TOKEN_ARROW:         return "token_arrow";
        case TOKEN_DOT:           return "token_dot";

        // Ternary Operator
        case TOKEN_QMARK:         return "token_qmark";
        case TOKEN_COLON:         return "token_colon";

        // Delimiters
        case TOKEN_SEMICOLON:     return "token_semicolon";
        case TOKEN_COMMA:         return "token_comma";
        case TOKEN_OPEN_PAREN:    return "token_open_paren";
        case TOKEN_CLOSE_PAREN:   return "token_close_paren";
        case TOKEN_OPEN_BRACE:    return "token_open_brace";
        case TOKEN_CLOSE_BRACE:   return "token_close_brace";
        case TOKEN_OPEN_BRACKET:  return "token_open_bracket";
        case TOKEN_CLOSE_BRACKET: return "token_close_bracket";

        // Literals
        case TOKEN_INT_LIT:       return "token_int_lit";
        case TOKEN_HEX_LIT:       return "token_hex_lit";
        case TOKEN_FLOAT_LIT:     return "token_float_lit";
        case TOKEN_CHAR_LIT:      return "token_char_lit";
        case TOKEN_STR_LIT:       return "token_str_lit";

        // Identifiers
        case TOKEN_IDENT:         return "token_ident";
        default:                  return "unexpected token";
    }
}

void print_token(token_t token) {
    printf("kind: %s, lexeme interval: (%ld, %ld)\n", kind_to_str(token.kind), token.lexeme.start, token.lexeme.end);
}


