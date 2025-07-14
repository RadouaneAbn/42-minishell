# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main()
{
	int fdo = open("out", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	int bo = dup(1);

	dup2(fdo, 1);

	printf("this goes to file\n");

	dup2(1, bo);

	printf("this goes to stdout\n");

	close (fdo);
}
