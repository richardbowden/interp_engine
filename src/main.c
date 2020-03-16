#include <stdio.h>

#include "interp_engine.h"
#include "lsd_string.h"
#include <stdbool.h>

// #include <strings.h>

char* token_to_find = "directory.bin";
char* test_str = "/home/${directory.bin}";
char* replacement_str = "mybindir";

int main()
{
    tok_pos* tokens;
    int res = ie_find_tokens(test_str, &tokens);

    printf("%d\n", res);

    // char* res = replace_token(test_str, token_to_find, replacement_str);
    if (res == -1) {
        printf("token parsing failed\n");
    }

    lsd_string* s = lsd_string_new(test_str, true);
    printf("str: %s\n", s->str);
    printf("len: %d\n", s->len);
    printf("tok: %d\n", s->num_tokens);
    printf("tok_parsed: %d\n", s->tok_parsed);

    return EXIT_SUCCESS;
}
