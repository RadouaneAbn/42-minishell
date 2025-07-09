#ifndef TEST_H
#define TEST_H

#include <minishell.h>

#include <stdio.h>
#include <string.h>

void test_export(char **env);

typedef struct s_status
{
    int success;
    int failure;
} t_status;

#endif