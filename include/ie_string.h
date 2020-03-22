#if !defined(__IE_STRING)
#define __IE_STRING
#include "interp_engine.h"
#include <stdbool.h>

int ie_string_err;

enum ie_string_errors {
    IE_STR_OK,
    IE_STR_NOT_PARSED,
    IE_STR_TOK_REPLACE_COUNT_MISS_MATCH,
};

typedef struct ie_token_s {
    tok_pos* pos;
    char* tok_inner_str;
    char* token;
} ie_token;

/**
 * 
 * 
 */
typedef struct ie_string_s {
    char* str;
    int len;
    int num_tokens;
    bool tok_parsed;

    tok_pos** tokens; /**< array of tok_pos* pointers. this is a pointer to a pointer */
} ie_string;

ie_string* ie_string_new(char* str, bool tok_parse);

/**
 * @brief get the token string for token x
 * @param[:in] str the ie_string to get the token from
 * @param[:in] num the token number in the string
 */
char* ie_string_get_token(ie_string* str, int num);

/**
 * @brief replaces all tokens in a string
 * @param[:in] str
 * @param[:in] replacements
 * @param[:in ] total
 * @param[:out ] char

*/
char* ie_string_replace_all_tokens(ie_string* str, char* replacements[], int total);

char* ie_string_replace_token(ie_string* str, char* replacement, int tok_num);

void ie_string_replace_tokenn(tok_pos tok, char* str, int str_len, char* replacement, char* buf);

#endif // __IE_STRING
