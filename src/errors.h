#pragma once 

typedef enum {
    CODE_SUCCESS,
    CODE_OBJECTLIST_FULL
} ErrorCode;

typedef struct {
    ErrorCode const code;
    char const * const msg;
} ERR_t;

ERR_t const SUCCESS = {CODE_SUCCESS, ""};
ERR_t const ERR_OBJECTLIST_FULL = {CODE_OBJECTLIST_FULL, "Object List Full"};
