#include "../../../src/frontend/lexer/includes/lexer.h"

int main(void) {
    // TODO: Check whether it should be 2 increments or one increment and 2 pluses 
    lexer_t lexer = new_lexer("++++", 2);
    token_vec tokens = {0};
    tokenize(&lexer, &tokens);

    print_tokens(tokens);
}

