#include "interp_engine.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ie_state = TOK_NONE; // state of the parse
static int ie_pos = 0; // current pos of the parse
static int matched = 0; // number of match tokens, 0 = none
static char* string; // the string to parse
static int str_len = 0;

static void parse_token(tok_pos* tok)
{
    ie_state = TOK_NONE;

    int tok_start;
    int start;
    int dot_pos = 0;

    if (string[ie_pos + 1] != '{') {
        ie_state = TOK_NOT_FOUND;
        return;
    }

    tok_start = ie_pos;

    //eat the $ and {
    ie_pos++;
    ie_pos++;

    //TODO: maybe check if this is >a and <z upper and lower
    start = ie_pos;

    int dot_counter = 0;

    // token* t = malloc(sizeof(token));

    /*TODO: add these checks to the below switch statement
     * 
     * invalid 33 to 45 and 47 
     *
     * valid
     * 46 = .
     * 48 to 57 0 to 9
     * 65 to 90 = capitals
     * 97 to 122 = lower case
     */
    char cur = string[ie_pos];

    while (cur != '\0') {

        switch (cur) {

        //TODO add more invalid chars to lookup table
        case '$': {
            //NOTE: currently we just skip a double $ and continue
            ie_state = TOK_INVALID_CHAR;
            return;
            break;
        }
            /* case 'a' ... 'z': */
            /* case 'A' ... 'Z': */

        case '}': {
            tok->tok_start = tok_start;
            tok->tok_end = ie_pos;
            tok->str_start = start;
            tok->str_end = ie_pos - 1;
            tok->tok_len = ie_pos - tok_start;
            tok->str_len = (ie_pos)-start;
            tok->dot_pos = dot_pos;
            ie_state = TOK_FOUND;
            return;
            break;
        }
        case '.': {
            dot_counter++;
            dot_pos = ie_pos;
            cur = string[++ie_pos];
            break;
        }

        default: {
            cur = string[++ie_pos];
        }
        }
    };

    //TODO maybe remove as this is prob never hit, as we either match and return 0 or reach EOF

    if (cur == '\0') {
        ie_state = TOK_EOF;
    } else {
        ie_state = TOK_NOT_FOUND;
    }
    
    return;
}

int ie_find_tokens(char* str, tok_pos** tokens)
{
    assert(tokens != NULL);

    tok_pos* tok_array = calloc(2, sizeof(tok_pos));
    *tokens = tok_array;

    //RESET
    ie_state = TOK_NONE; // state of the parse
    ie_pos = 0; // current pos of the parse
    matched = 0; // number of match tokens, 0 = none
    str_len = 0;

    string = str;
    str_len = strlen(string);

    //you need at least 4 chars to make a valid token, bail if not met
    if (str_len < 4) {
        ie_state = TOK_NOT_ENOUGH_CHARS;
        return -1;
    }

    char cur = *string;

    while (cur != '\0') {
        switch (cur) {
        case '$': {

            //handle double $
            if ((string[ie_pos + 1] == '$') && (ie_pos < str_len)) {
                //skipping, move forward to eat the second $
                ie_pos++;
                break;
            }

            if (string[ie_pos + 1] != '{') {
                break;
            }

            //safe to assume we may have a token
            tok_pos tok;
            parse_token(&tok);

            if (ie_state == TOK_EOF) {
                free(tok_array);
                ie_state = TOK_NOT_FOUND;
                return -1;
            }

            if (ie_state == TOK_INVALID_CHAR) {
                free(tok_array);
                return -1;
            }

            if (matched == 2) {
                tok_array = realloc(tok_array, (matched + 1) * sizeof(tok_pos));
            }

            *(tok_array + matched) = tok;

            matched++;
            break;
        }
        }
        ie_pos++;
        cur = string[ie_pos];
    }

    if (matched == 0) {
        if (tok_array != NULL) {
            free(tok_array);
        }

        ie_state = TOK_NOT_FOUND;
        return -1;
    }

    *tokens = tok_array;
    return matched;
}

tok_pos* ie_new_tokens_array()
{
    tok_pos* t = calloc(2, sizeof(tok_pos));
    return t;
}

int ie_get_error_pos()
{
    return ie_pos;
}

int ie_get_state()
{
    return ie_state;
}
