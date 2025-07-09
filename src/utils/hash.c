#include <minishell.h>

unsigned int hash(const char *key)
{
    unsigned int hash = 5381;
	int i;

	i = 0;
    while (key[i]) {
        hash = ((hash << 5) + hash) + key[i];
		i++;
    }

    return (hash % MAP_SIZE);
}