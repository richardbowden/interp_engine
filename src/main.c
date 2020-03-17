#include <stdio.h>

#include "ie_string.h"
#include "interp_engine.h"
#include <stdbool.h>

char* token_to_find = "directory.bin";
char* test_str = "/home/${directory.bin}";
char* replacement_str = "mybindir";

int main()
{
    tok_pos* tokens;
    int res = ie_find_tokens(test_str, &tokens);

    printf("%d\n", res);

    if (res == -1) {
        printf("token parsing failed\n");
    }

    ie_string* s = ie_string_new(test_str, true);
    printf("str: %s\n", s->str);
    printf("len: %d\n", s->len);
    printf("tok: %d\n", s->num_tokens);
    printf("tok_parsed: %d\n", s->tok_parsed);

    return EXIT_SUCCESS;
}
