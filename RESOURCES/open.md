# OPEN

<p style="color: lime">PROTOTYPE:</p>
```c
#include <fcntl.h>

int	open(const char *path, int oflag, ...);
```

<p style="color: lime">VALUES FOR OFLAG:</p>
* <span style="color: #BD93F9"> O_EXEC: </span>open for execute only (non-directory files). The result is unspecified if this flag is applied to a directory.
* <span style="color: #BD93F9">O_RDONLY</span> Open for reading only.
  <span style="color: #BD93F9">O_RDONLY:</span> Open for reading only.
* <span style="color: #BD93F9">O_RDWR:</span> open for reading and writing. The result is undefined if this flag is applied to a FIFO.  
* <span style="color: #BD93F9">O_WRONLY:</span> Open for writing only.
* <span style="color: #BD93F9">O_APPEND:</span> If set, the file offset shall be set to the end of the file prior to each write.
* <span style="color: #BD93F9">O_SEARCH:</span> Open directory for search only. The result is unspecified if this flag is applied to a non-directory file.
* <span style="color: #BD93F9">O_CREAT:</span> If the file exists, this flag has no effect except as noted under O_EXCL below, Otherwise, if O_DIRECTORY is 
not set the file shall be created as a regular file;
* <span style="color: #BD93F9">O_TRUNC:</span> If the file exists and is a regular file, and the file is successfully opened O_RDWR or O_WRONLY, its length shall be truncated to 0, and the mode and owner shall be unchanged. It  shall have  no effect on FIFO special files or terminal device files. Its effect on other file types is implementation-defined. The result of using O_TRUNC without either O_RDWR or O_WRONLY is undefined.

* <span style="color: #BD93F9">O_DIRECTORY:</span> If path resolves to a non-directory file, fail and set errno to <span style="color: yellow">ENOTDIR</span>.

<p style="color: lime">EXAMPLES: </p>

<span style="background-color: #BD93F9; color: black">FLAGS: </span> O_DIRECTORY | OCREAT | O_RDWR | O_WRONLY | O_RDONLY
<span style="background-color: #BD93F9; color: black">FUNCTIONS: </span> umask, mkdir, open, perror, remove, rmdir, printf, close

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int	main(void)
{

	// umask() sets the calling process’s file mode creation mask (umask) to mask & 0777. 
	//to read more about mask: https://man7.org/linux/man-pages/man2/umask.2.html, man 3 umask
	umask(0);

	char *dir_name = "dir";
	char *file_name = "file";

	//open a directory
	mkdir (dir_name, 0777);

	//check if 'dir' exists
	int fd = open(dir_name, O_DIRECTORY);

	if (fd == -1)
	{
		//if no such file or directory
		perror(dir_name);
	}
	else	
	{
		printf("%s exists\n", dir_name);
		close(fd);
	}

	fd = open(file_name, O_CREAT | O_RDWR, 0777);
	write(fd, "hello from c code", 17);
	close (fd);

	fd = open(file_name, O_DIRECTORY, 0755);

	if (fd == -1)
	{
		//if no such file or directory
		perror(file_name);
	}
	else	
	{
		printf("%s exists", file_name);
		close(fd);
	}
	
	//to remove a file
	remove(file_name);
	
	//to remove a directory
	rmdir(dir_name);


	return (0);
}
```

<p style="color: lime">OUTPUT: </p>
```bash
~ $ ls
main.c

~ $ cc main.c -o main

~ $ ./main
file: Not a directory
dir exists

~ $ ls
a.out main.c
```