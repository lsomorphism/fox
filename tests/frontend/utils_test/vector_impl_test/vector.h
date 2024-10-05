/* TODO:
    * Maybe add support for qualified generic types (const, static, etc)
    * Replace fprintf with a pretty printing logger
    * Maybe implement a delete function, might not be needed
    * Implement a "NAME##_insert_from" which takes an T* variable and embeds an array
    * Adapt "printer_fn_t" to maybe take in an "index" variable to support prettier printing
    * Test to see if vector supports array types, not 100% if it can or not
*/


#ifndef FOX_VECTOR_H_
#define FOX_VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>

// Note: Implementing generics with type-erasure becomes a headache down the road, I'll rewrite it to do "monomorphization" with macros

/*
== Example usage ==

#include <stdio.h>
#include vector.h

// You define your custom generic type here:
DEFINE_VEC_IMPL(int, int_vec)
DEFINE_VEC_IMPL(char, char_vec)

void print_int(int x)    { printf(x is: %d, x);   }
void print_char(char x2) { printf(x2 is: %c, x2); }

int main(void) {
    int_vec int_vec = {0};
    new_int_vec(&int_vec, 3);

    for(size_t i = 0; i <= 5; ++i) {
        int_vec_insert(&int_vec, i);
    }

    // No lambdas in C :(
    int_vec_printer(int_vec, print_int);

    char_vec char_vec = {0};
    new_char_vec(&char_vec, 3);

    char_vec_insert(&char_vec, 'A');
    char_vec_insert(&char_vec, 'B');
    char_vec_insert(&char_vec, 'C');

    char_vec_printer(char_vec, print_char);
}
*/
 
#define DEFINE_VEC_IMPL(T, NAME) \
    typedef struct { \
       T *vec_data; \
       size_t len, cap; \
    } NAME; \
    \
    bool new_##NAME(NAME *vec, size_t cap) { \
        if(!cap) { \
            fprintf(stderr, "[in new_%s()]: invalid capacity!\n", #NAME); \
            return false; \
        }\
        \
        *vec = (NAME) { \
            .vec_data = malloc(cap * sizeof(T)), \
            .len = 0, \
            .cap = cap \
        }; \
        \
        return true;\
    } \
    \
    bool NAME##_insert(NAME *vec, T data) { \
       if(!vec || !vec->vec_data || !vec->cap) { \
           fprintf(stderr, "[in %s_insert()]: invalid vector state!\n", #NAME); \
           return false; \
       } \
       \
       if(vec->len == vec->cap) { \
           vec->cap *= 2; \
           vec->vec_data = realloc(vec->vec_data, vec->cap * sizeof(T)); \
           \
           if(!vec->vec_data) { \
               fprintf(stderr, "[in %s_insert()]: failure to resize internal array in vector!\n", #NAME); \
               return false; \
           } \
           \
       } \
       \
       vec->vec_data[vec->len] = data; \
       vec->len += 1; \
       \
       return true; \
    } \
    \
    size_t NAME##_get(NAME *vec, T data) { \
        if(!vec || !vec->vec_data || !vec->cap) { \
            fprintf(stderr, "[in %s_get()]: invalid vector state!\n", #NAME); \
        } \
        \
        for(size_t i = 0; i < vec->len; ++i) { \
            if(vec->vec_data[i] == data) { \
                return i; \
            } \
        } \
        \
        return -1; \
    } \
    \
    void NAME##_printer(NAME vec, void (*printer)(T)) { \
      for(size_t i = 0; i < vec.len; ++i) { \
          printer(vec.vec_data[i]); \
      } \
    } \
    \
    bool delete_##NAME(NAME *vec) { \
        if(!vec || !vec->vec_data) { \
            fprintf(stderr, "[in delete_%s()]: Invalid vector state!\n", #NAME); \
            return false; \
        } \
        \
        free(vec->vec_data); \
        vec->vec_data = NULL; \
        \
        return true; \
    } \
        
/* == OLD CODE == */

/*
// Note: extra notes in the previous code just to fix some issues I noticed 

typedef struct {
   void *alloc;
   size_t size;
   size_t capacity;
} Vector;

// fix summary: 


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
