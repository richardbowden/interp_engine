#include "ie_string.h"
#include "interp_engine.h"
#include <assert.h>
#include <string.h>

int ie_string_err;

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

char* _ie_get_token(ie_string* str, int num)
{
    assert(str != NULL);

    if ((str->tok_parsed == false) && (str->num_tokens <= 0)) {
        return NULL;
    }

    if (num > str->num_tokens) {
        return NULL;
    }
    return (*str->tokens + num - 1)->tok_str;
}

char* ie_string_get_token(ie_string* str, int num)
{
    return _ie_get_token(str, num);
}

char* ie_string_replace_all_tokens(ie_string* str, char* replacements[], int num_replacements)
{
    if (str->num_tokens != num_replacements) {
        ie_string_err = IE_STR_TOK_REPLACE_COUNT_MISS_MATCH;
        return NULL;
    }

    char tmp_buffer[4096]; /** max path len on most systems, nothing should be this many char's, is so i will eat my hat */
    char ttt[4096];

    //set the str before we start.
    strcpy(tmp_buffer, str->str);
    strcpy(ttt, str->str);

    printf("reverse: %s\n", replacements[num_replacements - 1]);

    for (long i = num_replacements; i > 0; i--) {
        printf("replacement: %s\n", replacements[i - 1]);
        ie_string_replace_tokenn((*str->tokens)[i-1], ttt, strlen(tmp_buffer), replacements[i - 1], tmp_buffer);
        strcpy(ttt, tmp_buffer);
        printf("");
    }

    //    for (size_t i = 0; i < num_replacements; i++) {
    //        printf("replacement: %s\n", replacements[i]);
    //        ie_string_replace_token2(str->tokens[i], ttt, strlen(tmp_buffer), replacements[i], i + 1, &tmp_buffer);
    //        strcpy(ttt, tmp_buffer);
    //        printf("building: %s\n", tmp_buffer);
    //    }
}

char* ie_string_replace_token(ie_string* str, char* replacement, int tok_num)
{
    //TODO: works for now, come back and relook at this

    assert(replacement != NULL);
    assert(tok_num > 0);
    assert(str->tok_parsed == true);

    tok_pos* t = (*str->tokens + tok_num - 1);

    int beging = t->tok_start;
    int len_replacement = strlen(replacement);
    int end = (str->len - t->tok_end);

    int new_len = beging + len_replacement + end + 1;

    char* new_str = calloc(new_len, sizeof(char));

    //copy pointer to allow us to move the pointer around without touching the original in str
    char* orig_str = str->str;

    //beging of the original string
    memcpy(new_str, orig_str, beging);
    new_str = new_str + beging;

    //copy in the replacement string
    memcpy(new_str, replacement, len_replacement);
    new_str = new_str + len_replacement;

    //check to see if the replacement is the end of the string, or if there are chars after, copy that part to the end of the new string
    if (t->tok_end + 1 != str->len) {
        orig_str = orig_str + t->tok_end + 1;
        memcpy(new_str, orig_str, end);
    }

    //move string pointer back to the start
    new_str = new_str - beging - len_replacement;

    //be good and terminate the string
    new_str[new_len - 1] = '\0';
    return new_str;
}

void ie_string_replace_tokenn(tok_pos tok, char* str, int str_len, char* replacement, char* buf)
{
    //TODO: works for now, come back and relook at this

    assert(replacement != NULL);
    //    assert(tok_num > 0);

    int beging = tok.tok_start;
    int len_replacement = strlen(replacement);
    int end = (str_len - tok.tok_end);

    int new_len = beging + len_replacement + end + 1;

    // char* new_str = calloc(new_len, sizeof(char));

    //copy pointer to allow us to move the pointer around without touching the original in str
    char* orig_str = str;

    //beging of the original string
    memcpy(buf, orig_str, beging);
    buf = buf + beging;

    //copy in the replacement string
    memcpy(buf, replacement, len_replacement);
    buf = buf + len_replacement;

    //check to see if the replacement is the end of the string, or if there are chars after, copy that part to the end of the new string
    if (tok.tok_end + 1 != str_len) {
        orig_str = orig_str + tok.tok_end + 1;
        memcpy(buf, orig_str, end);
    }

    //move string pointer back to the start
    buf = buf - beging - len_replacement;

    //be good and terminate the string
    buf[new_len - 1] = '\0';
    return;
}
