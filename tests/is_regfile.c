#include <stdio.h>
#include <sys/stat.h>


int main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
		return (0);

	//get the file name
	char *filename = argv[1];

	struct stat info;

	int value = stat(filename, &info);

	printf("%s %s %d\n",filename, S_ISREG(info.st_mode) ? "is a regular file" : "is not a regular file", value);
}
