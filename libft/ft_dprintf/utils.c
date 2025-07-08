#include "ft_dprintf.h"
#include "../libft.h"

char	*convert(char *result, unsigned long n, char *base, bool is_signed)
{
	int	k;
	int	blen;

	blen = ft_strlen(base);
	k = 31;
	result[k--] = 0;
	if (n == 0)
		result[k--] = '0';
	while (n)
	{
		result[k--] = base[n % blen];
		n /= blen;
	}
	if (is_signed)
		result[k--] = '-';
	return (result + k + 1);
}

int ft_putchar_fd2(int fd, char c)
{
	return (write(fd, &c, 1));
}

int ft_putstr_fd2(int fd, char *s)
{
	char *new_s;

	new_s = s;
	if (new_s == NULL)
		new_s = "(null)";
	return (write(fd, new_s, ft_strlen(new_s)));
}
