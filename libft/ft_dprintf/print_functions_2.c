#include "ft_dprintf.h"

int	print_char(int fd, va_list args)
{
    int c;

    c = va_arg(args, int);
    return (ft_putchar_fd2(fd, c));
}

int	print_str(int fd, va_list args)
{
    char *s;

    s = va_arg(args, char *);
    return (ft_putstr_fd2(fd, s));
}

int	print_mod(int fd, va_list args)
{
    (void) args;
    return (ft_putchar_fd2(fd, '%'));
}