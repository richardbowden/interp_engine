#if !defined(__IE_STRING)
#define __IE_STRING
#include "interp_engine.h"
#include <stdbool.h>

typedef struct ie_token_s {
    tok_pos* pos;
    char* tok_inner_str;
    char* token;
} ie_token;

typedef struct ie_string_s {
    char* str;
    int len;
    int num_tokens;
    bool tok_parsed;

    //    ie_token *tokens;
    tok_pos** tokens;
} ie_string;

ie_string* ie_string_new(char* str, bool tok_parse);

char * ie_string_get_token(ie_string* str, int num);
char * ie_string_replace_token(ie_string* str, char *replacement, int tok_num);


#endif // __IE_STRING
