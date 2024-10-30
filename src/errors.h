#pragma once 

typedef enum {
    CODE_SUCCESS,
    CODE_OBJECTLIST_FULL
} ErrorCode;

typedef struct {
    ErrorCode const code;
    char const * const msg;
} ERR_t;

ERR_t extern const SUCCESS;
ERR_t extern const ERR_OBJECTLIST_FULL;
