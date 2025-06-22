#ifndef ENV_H
#define ENV_H

#include <hashmap.h>

struct s_info
{
	t_map exports;
	char **path;
	int last_exit_status;
	int env_size;
} t_info;

#endif