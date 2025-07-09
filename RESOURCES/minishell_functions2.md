<h3 style="color: #50FA7B">getcwd</h3>
```c
char *getcwd(char *buf, size_t size);
```

* getcwd returns a null-terminated string containing an absolute pathname that is the current working directory of the calling process. The pathname is returned as the function result and via the argument buf, if present;

* The  getcwd() function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.

* If the length of the absolute pathname of the current working directory, including the terminat‐ing  null byte, exceeds size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error, and allocate a larger buffer if necessary.

* if buff == NULL, getcwd allocates aough memory (malloc) to store the absolute pathname and return a pointer to it, so the user should free the pointer;
```c
#include <unistd.h>

int main(void)
{
	char *CWD = getcwd(NULL, 1024);

	printf("absolute pathname is: %s", CWD);

	free (CWD);

	return (0);
}
```

* if buff is NULL and size is less than the size of the absolute path getcwd allocates enough memory and exceeds the var size;
```c
#include <unistd.h>

int main(void)
{
	//0 is less than any apsolute path
	//but this will word just fine
	char *CWD = getcwd(NULL, 0);

	printf("absolute pathname is: %s", CWD);

	free (CWD);

	return (0);
}
```

> RETURN VALUE
* On success, these functions(getwd, getcwd, get_current_dir_name) return a pointer to a string containing the pathname of the current working directory.  In the case of getcwd() and getwd() this is the same value as buf.

* On failure, these function (getwd, getcwd, get_current_dir_name) return NULL, and errno is set to indicate the error.  The contents of the array pointed to by buf are undefined on error. 

> ERRORS:

* EACCES Permission to read or search a component of the filename was denied.

* EFAULT buf points to a bad address.

* EINVAL The size argument is zero and buf is not a null pointer.

* ENAMETOOLONG
       getwd(): The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.

* ENOENT The current working directory has been unlinked.

* ENOMEM Out of memory.

* ERANGE The size argument is less than the length of the absolute pathname of the working directory, including the terminating null byte.  You need to allocate a bigger array and try again.
