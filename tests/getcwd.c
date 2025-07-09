#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	char *CWD;

	CWD = getcwd(NULL, 0);
	printf("%s %d %d\n", CWD, errno, ENOENT);

	free(CWD);
}
