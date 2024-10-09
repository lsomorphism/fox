/* TODO:
    * Maybe add support for qualified generic types (const, static, etc)
    * Replace fprintf with a pretty printing logger
    * Maybe implement a delete function, might not be needed
    * Implement a "NAME##_insert_from" which takes an T* variable and embeds an array
    * Adapt "printer_fn_t" to maybe take in an "index" variable to support prettier printing
    * Test to see if vector supports array types, not 100% if it can or not
    * Use optional monad for error handling (requires: fixing project layout)
*/

// Note: Implementing generics with type-erasure becomes a headache down the road, I'll rewrite it to do "monomorphization" with macros

#ifndef FOX_VECTOR_H_
#define FOX_VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>

/*
== Example usage ==

#include <stdio.h>
#include "vector.h"

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
*/

#define DEFAULT_VEC_CAP 32
 
#define DECL_VEC(T, NAME)                                                                                   \
    typedef struct {                                                                                        \
       T *vec_data;                                                                                         \
       size_t vec_len, vec_cap;                                                                             \
    } NAME;                                                                                                 \
                                                                                                            \
    bool new_##NAME(NAME *);                                                                                \
    bool NAME##_reserve(NAME *, size_t);                                                                    \
    bool NAME##_insert(NAME *, T);                                                                          \
    size_t NAME##_get(const NAME *, T, bool (*)(T, T));                                                     \
    void NAME##_printer(const NAME *vec, void (*)(T));                                                      \
    bool delete_##NAME(NAME *);                                                                             \

#define DEFINE_VEC(T, NAME)                                                                                 \
    bool new_##NAME(NAME *vec) {                                                                            \
        if(!vec) {                                                                                          \
            fprintf(stderr, "[in new_%s()]: invalid vector state!\n", #NAME);                               \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        T *vec_data = malloc(DEFAULT_VEC_CAP * sizeof(*vec_data));                                          \
        if(!vec_data) {                                                                                     \
            fprintf(stderr, "[in new_%s()]: failure to allocate internal array!\n", #NAME);                 \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        *vec = (NAME) {                                                                                     \
            .vec_data = vec_data,                                                                           \
            .vec_len = 0,                                                                                   \
            .vec_cap = DEFAULT_VEC_CAP                                                                      \
        };                                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    bool NAME##_reserve(NAME *vec, size_t cap) {                                                            \
                if(!vec) {                                                                                  \
            fprintf(stderr, "[in new_%s()]: invalid vector state!\n", #NAME);                               \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        T *vec_data = malloc(cap * sizeof(*vec_data));                                                      \
        if(!vec_data) {                                                                                     \
            fprintf(stderr, "[in new_%s()]: failure to allocate internal array!\n", #NAME);                 \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        *vec = (NAME) {                                                                                     \
            .vec_data = vec_data,                                                                           \
            .vec_len = 0,                                                                                   \
            .vec_cap = cap                                                                                  \
        };                                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    bool NAME##_insert(NAME *vec, T data) {                                                                 \
        if(!vec || !vec->vec_data || !vec->vec_cap) {                                                       \
           fprintf(stderr, "[in %s_insert()]: invalid vector state!\n", #NAME);                             \
           return false;                                                                                    \
        }                                                                                                   \
                                                                                                            \
        if(vec->vec_len == vec->vec_cap) {                                                                  \
            vec->vec_cap *= 2;                                                                              \
            vec->vec_data = realloc(vec->vec_data, vec->vec_cap * sizeof(T));                               \
                                                                                                            \
            if(!vec->vec_data) {                                                                            \
                fprintf(stderr, "[in %s_insert()]: failure to resize internal array in vector!\n", #NAME);  \
                return false;                                                                               \
           }                                                                                                \
                                                                                                            \
        }                                                                                                   \
                                                                                                            \
        vec->vec_data[vec->vec_len] = data;                                                                 \
        vec->vec_len += 1;                                                                                  \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
                                                                                                            \
    size_t NAME##_get(const NAME *vec, T data, bool (*cmper)(T, T)) {                                       \
        if(!vec->vec_data || !vec->vec_cap) {                                                               \
            fprintf(stderr, "[in %s_get()]: invalid vector state!\n", #NAME);                               \
            return -1;                                                                                      \
        }                                                                                                   \
                                                                                                            \
        for(size_t i = 0; i < vec->vec_len; ++i) {                                                          \
            if(cmper(vec->vec_data[i], data)) {                                                             \
                return i;                                                                                   \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return -1;                                                                                          \
    }                                                                                                       \
                                                                                                            \
    void NAME##_printer(const NAME *vec, void (*printer)(T)) {                                              \
      for(size_t i = 0; i < vec->vec_len; ++i) {                                                            \
          printer(vec->vec_data[i]);                                                                        \
      }                                                                                                     \
    }                                                                                                       \
                                                                                                            \
    bool delete_##NAME(NAME *vec) {                                                                         \
        if(!vec || !vec->vec_data) {                                                                        \
            fprintf(stderr, "[in delete_%s()]: Invalid vector state!\n", #NAME);                            \
            return false;                                                                                   \
        }                                                                                                   \
                                                                                                            \
        free(vec->vec_data);                                                                                \
        vec->vec_data = NULL;                                                                               \
                                                                                                            \
        return true;                                                                                        \
    }                                                                                                       \
        
/* == OLD CODE == */

/*
// Note: extra notes in the previous code just to fix some issues I noticed 

typedef struct {
   void *alloc;
   size_t size;
   size_t capacity;
} Vector;

bool vector_init(Vector *vec, size_t capacity) {
   // ensure the initialization size isn't 0:
   if(!size) {
      // print error
      return false;
   }

   // not enough space, should be: malloc(size * sizeof(void *))
   vec->alloc = malloc(size);
   if (vec->alloc == NULL) {
      return false;
   }

   vec->size = 0;
   vec->capacity = size;
   
   return false;
}

static inline void vector_deinit(Vector *vec) {
   free(vec->alloc);
}

static inline int vector_reserve(Vector *vec, size_t addtl_size) {
   size_t min_size = vec->size + addtl_size;
   if (vec->capacity >= min_size) {
      return 1;
   }

   void *alloc = realloc(vec->alloc, min_size);
   if (alloc == NULL) {
      return 0;
   }

   vec->alloc = alloc;
   vec->capacity += addtl_size;
   return 1;
}
*/

#endif // !FOX_VECTOR_H_


