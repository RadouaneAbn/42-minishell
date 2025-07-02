#include <sys/stat.h>
#include <stdbool.h>


bool is_dir(char *filename)
{
	struct stat info;

	lstat(filename, &info);
	return (S_ISLNK(info.st_mode));
}

bool is_sym(char *filename)
{
	struct stat info;

	lstat(filename, &info);
	return (S_ISLNK(info.st_mode));
}
// int main(int argc, char **argv)
// {
// 	printf("%d\n", is_dir(argv[1]));
// 	return (0);
// }
