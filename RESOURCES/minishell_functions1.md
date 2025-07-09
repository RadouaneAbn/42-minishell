<h3 style="color: #50FA7B">rl_clear_history</h3>
```c
#include <sys/stat.h>

int	stat(const char *pathname, struct stat *statbuf);
```

* stat returns information about a file name;
> EXAMPLES:

print filename size
```c
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
	printf("%s size is: %d\n", filename, info.st_size);
}
```

check if filename is a regular file:
```c
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
		return (0);

	//get the file name
	char *filename = argv[1];

	struct stat info;

	stat(filename, &info);

	printf("%s %s\n",filename, S_ISREG(info.st_mode) ? "is a regular file" : "is not a regular file");
}

```

> RETURN VALUE:
* On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

