#ifndef BUILT_IN_H
#define BUILT_IN_H

#include <hashmap.h>

t_map   *get_map();
char **split_export_args(char *arg);

int     echo(char **vec);
int     export(char *key, char *value);
int     unset(char *key);
char    *expand_env(char *key);
int     pre_export(char *exported);
int print_env();
int print_exports();

#endif