#ifndef ENV_H
#define ENV_H

#include "hash_map.h"

struct s_shell
{
	char **env;
	t_map exports;
	char **path;
	int last_exit_status;
	int env_size;
};

#endif