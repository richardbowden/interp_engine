#include "ie_string.h"
#include "interp_engine.h"
#include <string.h>

ie_string* ie_string_new(char* str, bool tok_parse)
{
    ie_string* s = calloc(1, sizeof(ie_string));
    s->str = strdup(str);
    s->len = strlen(str);
    s->tok_parsed = false;

    if (tok_parse) {
        *(s->tokens) = ie_new_tokens_array();
        int count = ie_find_tokens(str, s->tokens);
        if (count > 0) {
            s->num_tokens = count;
            s->tok_parsed = true;
        }
    }

    return s;
}

// int ie_string_parse(ie_string *str){

// }