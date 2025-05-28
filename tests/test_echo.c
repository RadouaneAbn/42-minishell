#include "tests.h"

void no_expanding_tests()
{
    int i;
    char *vec[][10] = {
        {"hello", "world", NULL},
        {"-", "-", "-", NULL},
        {"-n", "-> NO new line", NULL},
        {"-nnnnnnnnnnnn", "-> NO new line", NULL},
        {"-nnnn", "-nnnn", "-> NO new line", NULL},
        {"-h", "unkown flag", NULL},
        {"-nh", "unkown flag", NULL},
        {"-n", "-h", "no new line and unkown flag", NULL},
        {"-h", "-n", "unkown flag", NULL},
        {"-n", NULL},
        {"", NULL},
        {NULL}
    };

    i = 0;
    while (vec[i][0])
    {
        echo(vec[i]);
        i++;
    }
}

void test_echo(char **env)
{
    (void) env;
    no_expanding_tests();
}