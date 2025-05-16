#include <string.h>
#include <stdio.h>

int main(int ac , char ** av, char **env)
{
	printf("%p\n", env[0]);

	return (1002);
}
