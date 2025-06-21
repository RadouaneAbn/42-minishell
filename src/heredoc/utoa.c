#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// this function returns the length of a number like:
// ex: get 1000 => return 4
static int	utoa_length(size_t number)
{
	int	length;

	length = 1;
	while (number >= 10)
	{
		number = number / 10;
		length++;
	}
	return (length);
}

// this function fills memory block ptr with chars
// from the unsigned number
static void	utoa_fill(char *ptr, size_t number, int end, int start)
{
	while (end >= start)
	{
		*(ptr + end) = number % 10 + '0';
		number /= 10;
		end--;
	}
}

// this function returns and allocates enough memory for
// all chars in an unsgined int
// get 10 => returns "10"
char	*utoa(size_t num)
{
	int		length;
	char	*ptr;
	int		start;

	start = 0;
	length = utoa_length(num);
	ptr = (char *)malloc((length + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	*(ptr + length) = '\0';
	utoa_fill(ptr, num, length - 1, start);
	return (ptr);
}
