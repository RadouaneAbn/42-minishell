#ifndef ENV_H
#define ENV_H

#include "hash_map.h"

typedef struct s_info
{
	char **env;
	t_map exports;
	char **path;
	int last_exit_status;
	int env_size;
} t_info;

t_info *get_info();

#endif