#include "tests.h"

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;

    hash_map_tests(env);
    test_echo(env);

    return (0);
}