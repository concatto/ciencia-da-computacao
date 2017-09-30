#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_open_scope = 2,
    t_close_scope = 3,
    t_end = 4,
    t_timer_start = 5,
    t_lit_interval = 6,
    t_ms = 7,
    t_repeat_start = 8,
    t_forever = 9,
    t_times = 10,
    t_if = 11,
    t_attrib = 12,
    t_open_paren = 13,
    t_close_paren = 14,
    t_comma = 15,
    t_gt = 16,
    t_gte = 17,
    t_lt = 18,
    t_lte = 19,
    t_eq = 20,
    t_neq = 21,
    t_plus = 22,
    t_minus = 23,
    t_mult = 24,
    t_div = 25,
    t_lit_string = 26,
    t_number = 27,
    t_variable = 28
};

const int STATES_COUNT = 66;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 47;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[65][51][2];

extern const int PRODUCTIONS[41][2];

extern const char *PARSER_ERROR[65];

#endif
