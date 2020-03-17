#include "ie_string.h"
#include "interp_engine.h"
#include <string.h>
#include <assert.h>

ie_string* ie_string_new(char* str, bool tok_parse)
{
    ie_string* s = calloc(1, sizeof(ie_string));
    s->tokens = malloc(sizeof(tok_pos*));
    s->str = strdup(str);
    s->len = strlen(str);
    s->tok_parsed = false;

    if (tok_parse) {
        *s->tokens = ie_new_tokens_array();
        int count = ie_find_tokens(str, s->tokens);
        if (count > 0) {
            s->num_tokens = count;
            s->tok_parsed = true;
        }
    }

    return s;
}

char * _ie_get_token(ie_string *str, int num){
    assert(str != NULL);
    
    if ((str->tok_parsed == false) && (str->num_tokens <= 0)){
        return NULL;
    }

    if (num > str->num_tokens){
        return NULL;
    }
    return (*str->tokens+num-1)->tok_str;
}

char * ie_string_get_token(ie_string* str, int num){
    return _ie_get_token(str, num);
}

char * ie_string_replace_token(ie_string* str, char *replacement, int tok_num){

    tok_pos * t = (*str->tokens+tok_num-1);
    
    int beging = t->tok_start;
    int len_replacement = strlen(replacement);
    int end = (str->len - t->tok_end);
    
    int new_len = beging + len_replacement + end +1;
    
    char * new_str = calloc(new_len, sizeof(char));
    char *orig_str = str->str;
    
    memcpy(new_str,orig_str , beging);
    new_str = new_str+beging;
    memcpy(new_str, replacement, len_replacement);
    new_str = new_str+len_replacement;
    
    if (t->tok_end+1 != str->len){
        orig_str = orig_str+t->tok_end+1;
        memcpy(new_str, orig_str, end);
    }
    
    new_str = new_str-beging-len_replacement;
    return new_str;
}
