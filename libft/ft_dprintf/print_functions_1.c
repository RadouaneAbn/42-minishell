#include "ft_dprintf.h"

int	print_dec(int fd, va_list args)
{
	char	result[32];
	int		n;
	char	*s;

	n = va_arg(args, int);
	if (n < 0)
		s = convert(result, -(unsigned long)(n), "0123456789", true);
	else
		s = convert(result, n, "0123456789", false);
	return (ft_putstr_fd2(fd, s));
}

int	print_udec(int fd, va_list args)
{
	char			result[32];
	unsigned int	n;
	char			*s;

	n = va_arg(args, unsigned int);
	s = convert(result, n, "0123456789", false);
	return (ft_putstr_fd2(fd, s));
}

int	print_hex_cap(int fd, va_list args)
{
	char			result[32];
	unsigned int	n;
	char			*s;

	n = va_arg(args, unsigned int);
	s = convert(result, n, "0123456789ABCDEF", false);
	return (ft_putstr_fd2(fd, s));
}

int	print_hex(int fd, va_list args)
{
	char			result[32];
	unsigned int	n;
	char			*s;

	n = va_arg(args, unsigned int);
	s = convert(result, n, "0123456789abcdef", false);
	return (ft_putstr_fd2(fd, s));
}

int	print_addr(int fd, va_list args)
{
	char			result[32];
	unsigned long	n;
	char			*s;

	n = va_arg(args, unsigned long);
	if (n == 0)
		return (ft_putstr_fd2(fd, "(nil)"));
	s = convert(result, n, "0123456789abcdef", false);
	*(--s) = 'x';
	*(--s) = '0';
	return (ft_putstr_fd2(fd, s));
}