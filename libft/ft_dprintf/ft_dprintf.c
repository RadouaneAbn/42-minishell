#include "ft_dprintf.h"

void	build_func(t_func (*functions)[10])
{
	(*functions)[0].flag = '%';
	(*functions)[1].flag = 'c';
	(*functions)[2].flag = 's';
	(*functions)[3].flag = 'i';
	(*functions)[4].flag = 'd';
	(*functions)[5].flag = 'u';
	(*functions)[6].flag = 'x';
	(*functions)[7].flag = 'X';
	(*functions)[8].flag = 'p';
	(*functions)[9].flag = 0;
	(*functions)[0].f = print_mod;
	(*functions)[1].f = print_char;
	(*functions)[2].f = print_str;
	(*functions)[3].f = print_dec;
	(*functions)[4].f = print_dec;
	(*functions)[5].f = print_udec;
	(*functions)[6].f = print_hex;
	(*functions)[7].f = print_hex_cap;
	(*functions)[8].f = print_addr;
	(*functions)[9].f = NULL;
}

t_func *get_functions(void)
{
    static t_func functions[10];

    if (functions[0].f == 0)
        build_func(&functions);
    return (functions);
}

int	find_flag(int fd, va_list args, const char *s, int *i)
{
    t_func *functions;
	int		n;
	int		start;

	start = *i;
	(*i)++;
	n = 0;
    functions = get_functions();
	while (functions[n].flag)
	{
		if (s[*i] == functions[n].flag)
			return (functions[n].f(fd, args));
		n++;
	}
	if (s[*i] == 0)
		return (-1);
	*i = start;
	return (print_mod(fd, args));
}

int	init_printf(int fd, const char *str, va_list args)
{
	int	i;
	int	tmp;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
			tmp = find_flag(fd, args, str, &i);
		else
			tmp = ft_putchar_fd2(fd, str[i]);
		if (tmp == -1)
			return (-1);
		count += tmp;
		i++;
	}
	return (count);
}

int ft_dprintf(int fd, const char *str, ...)
{
    int		count;
	va_list	args;

	if (str == NULL)
		return (-1);
	va_start(args, str);
	count = init_printf(fd, str, args);
	va_end(args);
	return (count);
}
