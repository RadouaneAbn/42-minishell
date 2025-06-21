#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

// O_DIRECTORY | OCREAT
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
