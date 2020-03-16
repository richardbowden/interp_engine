#include "interp_engine.h"
#include <stdio.h>

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test)  \
    do {               \
        if (!(test)) { \
            FAIL();    \
            return 1;  \
        }              \
    } while (0)
#define _verify(test)   \
    do {                \
        int r = test(); \
        tests_run++;    \
        if (r)          \
            return r;   \
    } while (0)

int tests_run = 0;

int test_simple_token()
{
    char* test_str = "${directory.test}";
    tok_pos* t;
    int count = ie_find_tokens(test_str, &t);

    _assert(count == 1);
    _assert(t->tok_start == 0);
    free(t);
    return 0;
}

int test_less_simple_token()
{
    char* test_str = "aaa${directory.test}";
    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    _assert(count == 1);
    _assert(test_str[t->tok_start] == '$');
    _assert(test_str[t->tok_end] == '}');
    _assert(test_str[t->str_start] == 'd');
    _assert(test_str[t->str_end] == 't');
    free(t);
    return 0;
}

int test_less_less_simple_token()
{
    char* test_str = "dasdasd${directory.test}ssasas";
    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);

    _assert(test_str[t->tok_start] == '$');
    _assert(test_str[t->tok_end] == '}');
    _assert(test_str[t->str_start] == 'd');
    _assert(test_str[t->str_end] == 't');
    _assert(count == 1);
    free(t);
    return 0;
}

int test_incomplete_token()
{
    char* test_str = "d${directory.ta";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    _assert(ie_get_state() == TOK_NOT_FOUND);
    _assert(count == -1);
    return 0;
}

int test_skip_double_token()
{
    char* test_str = "dasdasd$${directory.tesssasas}";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    _assert(ie_get_state() == TOK_NOT_FOUND);
    _assert(count == -1);
    return 0;
}

int test_skip_double_dollars_no_token()
{
    char* test_str = "dasdasd$$asdasd";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);

    _assert(count == -1);
    _assert(ie_get_state() == TOK_NOT_FOUND);
    return 0;
}

int doubletest()
{

    char* test_str = "aaa${a.a}/${b.b}";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    _assert(ie_get_state() == TOK_FOUND);
    _assert(count == 2);
    free(t);
    return 0;
}

int trippletest()
{

    char* test_str = "aaa${a.a}/${b.b}/${c.c}";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    _assert(ie_get_state() == TOK_FOUND);
    _assert(count == 3);
    free(t);
    return 0;
}

int test_dollar_inside_token()
{
    char* test_str = "aa${aa.bbb$bbb}sd";

    tok_pos* t = NULL;
    int count = ie_find_tokens(test_str, &t);
    
    _assert(count == -1);
    _assert(ie_get_state() == TOK_INVALID_CHAR);
    _assert(ie_get_error_pos() == 10);

    return 0;
}

int all_tests()
{
    _verify(test_simple_token);
    _verify(test_incomplete_token);
    _verify(test_less_simple_token);
    _verify(test_less_less_simple_token);
    _verify(test_skip_double_token);
    _verify(test_skip_double_dollars_no_token);
    _verify(doubletest);
    _verify(trippletest);
    _verify(test_dollar_inside_token);

    return 0;
}

int main(int argc, char** argv)
{
    int result = all_tests();
    if (result == 0)
        printf("passed\n");
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
