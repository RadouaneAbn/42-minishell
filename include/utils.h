#ifndef UTILS_H
#define UTILS_H

#include <env.h>

void *ft_malloc(size_t size);

int	ft_strcmp(const char *s1, const char *s2);
int ft_index_of(char *str, char c);
t_info *get_info(void);
void load_env(char **env);
bool is_dir(char *filename);

#endif