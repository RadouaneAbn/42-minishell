#include <sys/stat.h>


int main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
		return (0);

	//get the file name
	char *filename = argv[1];

	struct stat info;

	stat(filename, &info);

	//print the size of the file in bytes
	printf("%d\n", info.st_size);

	printf("%d\n", info.st_mode);
}
// source: https://codeforwin.org/c-programming/c-program-find-file-properties-using-stat-function
// https://www.youtube.com/watch?v=5k0Eh1ZpT0o
