#include <sys/stat.h>


int is_dir(char *filename)
{
	struct stat info;

	stat(filename, &info);
	return (S_ISDIR(info.st_mode));
}
int main(int argc, char **argv)
{
	printf("%d\n", is_dir(argv[1]));
	return (0);
}
