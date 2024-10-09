#ifndef FOX_LEXER_RESULT_H_
#define FOX_LEXER_RESULT_H_

#include <stdbool.h>
#include <stdlib.h>  

#define LOG_ERROR(msg)     \
    fprintf(stderr,        \
        "[Msg]: %s\n"      \
        "[Line]: %d\n"     \
        "[Func]: %s\n"     \
        "[File]: %s\n",    \
        msg,               \
        __LINE__,          \
        __func__,          \
        __FILE__           \
    ), exit(EXIT_FAILURE)  \

#define DECL_RESULT(name, T, E) \
    typedef struct {            \
        bool err_active;        \
        T ok;                   \
        E err;                  \
    } name;                     \

#define ok(name, ok_val)  ((name) { .err_active = false, .ok = ok_val, .err = 0 });

#define err(name, err_val) ((name) { .err_active = true, .err = err_val, .ok = 0 })

#define is_ok(result)  (!result.err_active)
#define is_err(result) (result.err_active)

#define get_ok(result) (!result.err_active ? result.ok  : (LOG_ERROR("Cannot access \"ok\" value while \"err\" is active"!), result.ok))
#define get_err(result) (result.err_active ? result.err : (LOG_ERROR("Cannot access \"err\" value while \"err\" is not active!"), result.err))

#endif
