#ifndef FT_DPRINTF_H
#define FT_DPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_func
{
	char	flag;
	int		(*f)(int, va_list);
}			t_func;

int ft_dprintf(int fd, const char *str, ...);

// size_t	ft_strlen(const char *s);
int ft_putchar_fd2(int fd, char c);
int ft_putstr_fd2(int fd, char *s);
char	*convert(char *result, unsigned long n, char *base, bool is_signed);
int	print_mod(int fd, va_list args);
int	print_dec(int fd, va_list args);
int	print_udec(int fd, va_list args);
int	print_hex_cap(int fd, va_list args);
int	print_hex(int fd, va_list args);
int	print_addr(int fd, va_list args);
int	print_char(int fd, va_list args);
int	print_str(int fd, va_list args);



#endif