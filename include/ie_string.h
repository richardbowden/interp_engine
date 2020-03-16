#if !defined(__IE_STRING)
#define __IE_STRING
#include "interp_engine.h"
#include <stdbool.h>

typedef struct ie_string_s {
    char* str;
    int len;
    int num_tokens;
    bool tok_parsed;
    tok_pos** tokens;
} ie_string;

ie_string* ie_string_new(char* str, bool tok_parse);
// int ie_string_parse(ie_string* str);

#endif // __IE_STRING
