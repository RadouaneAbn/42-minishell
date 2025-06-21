SOURCE_FILES = $(wildcard src/lexer/*.c)  $(wildcard src/parser/*.c) $(wildcard src/heredoc/*.c)  $(wildcard src/expansion/*.c) 
SOURCE_FILES_2 = $(wildcard src/execution/*.c)

OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)
OBJECT_FILES_2 = $(SOURCE_FILES_2:%.c=%.o)

TEST_FILES = tests/main.c \
	tests/hash_map.c \
	src/execution/hashmap.c \
	tests/test_echo.c \
	src/execution/echo.c
OBJECT_TEST_FILE = $(TEST_FILES:%.c=%.o)

CONSOLE_FILES = tests/console.c

UTILS = $(wildcard src/utils/*.c)
UTILS_OBJ = $(UTILS:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = include
TARGET = minishell

TESTS = minitest
CONSOLE = console_bin

all: $(TARGET)

$(TARGET): $(OBJECT_FILES) libft/libft.a
	$(CC) $^ -o $@  -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	$(RM) $(RM_OPTIONS) $(OBJECT_FILES) $(OBJECT_TEST_FILE)

libft/libft.a:
	make -C libft

fclean: clean
	$(RM) $(RM_OPTIONS) $(TARGET) $(TESTS)
	make fclean -C libft

re: fclean $(TARGET)

run: $(TARGET) clean
	clear
	./$(TARGET)

$(TESTS): $(OBJECT_TEST_FILE) libft/libft.a
	@$(CC) $^ -o $@
	@$(RM) $(OBJECT_TEST_FILE)

test: $(TESTS)
	./$(TESTS)

$(CONSOLE): $(OBJECT_FILES_2) $(UTILS_OBJ) $(CONSOLE_FILES) libft/libft.a
	@$(CC) -g3 $^ -o $@
	@$(RM) $(OBJECT_FILES_2)

console: $(CONSOLE)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(CONSOLE)

valgrind: re
	valgrind ./$(TARGET)


DATE = $(shell date +%F/%H/%M)

push:
	push "automatic push (minishell hsacr) $(DATE)"
