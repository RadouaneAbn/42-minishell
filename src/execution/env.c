#include "../../include/hash_map.h"
#include "../../include/env.h"
#include "../../include/utils.h"


char *build_var(char *key, char *value)
{
    char *s;
    int i;
    int j;
    int size;

    size = ft_strlen(key) + ft_strlen(value) + 2;
    s = malloc(sizeof(char) * size);
    i = 0;
    j = 0;
    while (key[j])
        s[i++] = key[j++];
    j = 0;
    s[i++] = '=';
    while (value[j])
        s[i++] = value[j++];
    s[i] = 0;
    return (s);
}

int add_to_env(char *key, char *value)
{
    t_info *info;
    char **env;
    char *env_var;
    int i;

    if (key == NULL || value == NULL)
        return (RETURN_SUCCESS);
    info = get_info();
    if (info == NULL)
        return (RETURN_FAILURE);
    env = info->env;
    i = 0;
    while (env[i])
        i++;
    if (i == info->env_size - 1)
    {
        env = ft_realloc(env, info->env_size, info->env_size * 2);
        if (env == NULL)
        
        info->env_size *= 2;
    }
    env_var = build_var(key, value);
    env[i++] = env_var;
    env[i] = NULL;
    return (RETURN_SUCCESS);
}