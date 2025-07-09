#include <sys/stat.h>
#include <stdbool.h>


bool is_dir(char *filename)
{
	struct stat info;

	stat(filename, &info);
	return (S_ISDIR(info.st_mode));
}

bool is_sym(char *filename)
{
	struct stat info;

	lstat(filename, &info);
	return (S_ISLNK(info.st_mode));
}
