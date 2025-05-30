SOURCE_FILES = $(wildcard src/lexer/*.c)  $(wildcard src/parser/*.c) $(wildcard src/heredoc/*.c) 
OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = include
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJECT_FILES) libft/libft.a
	$(CC) $^ -o $@  -lreadline
	

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	$(RM) $(RM_OPTIONS) $(OBJECT_FILES)

libft/libft.a:
	make -C libft

fclean: clean
	$(RM) $(RM_OPTIONS) $(TARGET)
	make fclean -C libft

re: fclean $(TARGET)

run: $(TARGET) clean
	clear
	./$(TARGET)

valgrind: re
	valgrind ./$(TARGET)


DATE = $(shell date +%F/%H/%M)

push:
	push "automatic push (minishell hsacr) $(DATE)"
