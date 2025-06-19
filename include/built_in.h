#ifndef BUILT_IN_H
#define BUILT_IN_H

t_map   *get_map();
char **split_export_args(char *arg);

int     echo(char **vec);
int     export(char *key, char *value);
int     unset(char *key);
char    *expand(char *key);

#endif