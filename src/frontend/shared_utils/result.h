#ifndef FOX_LEXER_RESULT_H_
#define FOX_LEXER_RESULT_H_

#include <features.h>
#include <stdbool.h>
#include <stdlib.h>  

#define LOG_ERROR(msg)            \
    fprintf(stderr,               \
        "[Msg]: %s\n"             \
        "[Func]: %s()\n"          \
        "[Location]: %s:%d\n",    \
        msg,                      \
        __func__,                 \
        __FILE__,                 \
        __LINE__                  \
    ), exit(EXIT_FAILURE)         \

#define DECL_RESULT(NAME, T, E)   \
    typedef struct {              \
        bool err_active;          \
        union {                   \
            T ok;                 \
            E err;                \
        } value;                  \
    } NAME;                       \

#define ok(name, ok_val)   ((name) { .err_active = false, .value.ok  = ok_val, })
#define err(name, err_val) ((name) { .err_active = true,  .value.err = err_val })

#define is_ok(result)  (!result.err_active)
#define is_err(result) (result.err_active)

#define get_ok(result)  (is_ok(result)  ? result.value.ok  : (LOG_ERROR("Cannot access \"ok\" value while \"err\" is active!"), result.value.ok))
#define get_err(result) (is_err(result) ? result.value.err : (LOG_ERROR("Cannot access \"err\" value while \"err\" is not active!"), result.value.err))

#endif

