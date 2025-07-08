MY_FILES = ft_tolower.c ft_toupper.c ft_isdigit.c ft_isascii.c ft_isalpha.c \
		ft_isalnum.c ft_isprint.c ft_strlen.c ft_strlcat.c ft_memchr.c \
		ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
		ft_atoi.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memcmp.c ft_bzero.c \
		ft_strnstr.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
	
BONUS_FILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJECTS = ${BONUS_FILES:.c=.o}
 
MY_OBJECTS = ${MY_FILES:.c=.o}

DPRINTF_SRC = ft_dprintf/ft_dprintf.c \
	ft_dprintf/print_functions_1.c ft_dprintf/print_functions_1.c \
	ft_dprintf/utils.c

DPRINTF_OBJ = $(DPRINTF_SRC:.c=.o)

CC = cc

CC_FLAGS = -c -Wall -Werror -Wextra

NAME = libft.a

all: ${NAME}

bonus: ${BONUS_OBJECTS} ${MY_OBJECTS} ${DPRINTF_OBJ}
	ar rcs ${NAME} $?

${NAME}: ${MY_OBJECTS} ${DPRINTF_OBJ}
	ar rcs ${NAME} $?

%.o: %.c libft.h
	${CC} ${CC_FLAGS} $< -o $@

clean:
	rm -rf  ${MY_OBJECTS} ${BONUS_OBJECTS} ${DPRINTF_OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean

