#include <stdio.h>
#include "../../../../src/vector.h"

DECL_VEC(int, int_vec)
DEFINE_VEC(int, int_vec)

DECL_VEC(char, char_vec)
DEFINE_VEC(char, char_vec)

void print_int(int x)    { printf("x is: %d\n", x);   }
void print_char(char x2) { printf("x2 is: %c\n", x2); }

int main(void) {
    int_vec int_vec = {0};
    new_int_vec(&int_vec);

    for(size_t i = 0; i <= 5; ++i) {
        int_vec_insert(&int_vec, i);
    }

    // No lambdas in C :(
    int_vec_printer(int_vec, print_int);

    char_vec char_vec = {0};
    new_char_vec(&char_vec);

    char_vec_insert(&char_vec, 'A');
    char_vec_insert(&char_vec, 'B');
    char_vec_insert(&char_vec, 'C');

    char_vec_printer(char_vec, print_char);

    delete_int_vec(&int_vec);
    delete_char_vec(&char_vec);
}

