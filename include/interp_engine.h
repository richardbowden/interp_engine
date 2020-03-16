#if !defined(__INTERP_ENGINE)
#define __INTERP_ENGINE
#include <stdio.h>
#include <stdlib.h>
/*
    basic version for now, NOT THREAD SAFE, calling ie_find_tokens will reset the internal state
*/

// typedef enum IE_PARSER_OPT_FLAGS {
//     IE_PARSER_OPT_NONE = 1 << 0,
//     IE_PARSER_OPT_IGNORE_DOUBLE_TOK_IDENTIFIER = 1 << 1,
// } IE_PARSER_OPT_FLAGS;

// IE_PARSER_OPT_FLAGS ie_parser_flags;

enum p_state {
    TOK_NONE,
    TOK_FOUND,
    TOK_PARTIAL,
    TOK_NOT_FOUND,
    TOK_INVALID_CHAR,
    TOK_NOT_ENOUGH_CHARS,

    TOK_EOF,
};

typedef struct token_s {
    int tok_start;
    int tok_end;
    int str_start;
    int str_end;
    int tok_len;
    int str_len;
    int dot_pos;
} tok_pos;

int ie_get_error_pos();
int ie_get_state();
int ie_find_tokens(char* str, tok_pos** tokens);

tok_pos* ie_new_tokens_array();

#endif // __INTERP_ENGINE
