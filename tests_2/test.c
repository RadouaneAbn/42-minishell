#include "test.h"

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    test_export(env);
}