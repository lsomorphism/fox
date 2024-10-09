#ifndef FOX_LEXER_OPTIONAL_H_
#define FOX_LEXER_OPTIONAL_H_

#include <stdio.h>
#include <stdlib.h>

#define TYPE_CONFLICT_ERR_MSG(func_name) "[ERROR in " #func_name "]: Mismatch data type for provided argument!"

#define UNWRAP_ERR(msg)                             \
    fprintf(stderr,                                 \
        "[Lexer ICE]: %s\n"                         \
        "[Line]: %d\n"                              \
        "[Func]: %s\n"                              \
        "[File]: %s\n",                             \
        msg,                                        \
        __LINE__,                                   \
        __func__,                                   \
        __FILE__                                    \
    ), exit(EXIT_FAILURE)                           \

#define IS_TYPE(T,U) _Generic((typeof(T)*) 0, typeof(U)*: true, default: false)

#define DECL_OPTIONAL(name, T)     \
    typedef struct {               \
        T value;                   \
        bool is_none;              \
    } name;                        \

#define some(name, optional_val) (name) { .is_none = false, .value = optional_val }

#define none(name) (name) { .is_none = true, .value = 0 }

#define unwrap(optional) (!optional.is_none ? optional.value : (UNWRAP_ERR("Unwrap on None()"), optional.value))

#define expect(optional, msg) (!optional.is_none ? optional.value : (UNWRAP_ERR(msg), optional.value))

#define unwrap_or(optional, failure_value) ({                                                      \
    _Static_assert(IS_TYPE(optional.value, failure_value), TYPE_CONFLICT_ERR_MSG("unwrap_or()"));  \
    !optional.is_none ? optional.value : failure_value;                                            \
})                                                                                                 \

#define unwrap_or_do(optional, func, ...) ({                                                             \
    _Static_assert(IS_TYPE(optional.value, func(__VA_ARGS__)), TYPE_CONFLICT_ERR_MSG("unwrap_or_do()")); \
    !optional.is_none ? optional.value : func(__VA_ARGS__);                                              \
})                                                                                                       \

#endif
