SOURCE_FILES = $(wildcard src/lexer/*.c)
OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)
TEST_FILES = tests/main.c \
	tests/hash_map.c \
	src/execution/hashmap.c \
	tests/test_echo.c \
	src/execution/echo.c

UTILS = $(wildcard src/utils/*.c)
OBJECT_TEST_FILE = $(TEST_FILES:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = include
TARGET = minishell

TESTS = minitest

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

re: fclean $(TARGET)

run: $(TARGET)
	clear
	./$(TARGET)

$(TESTS): $(OBJECT_TEST_FILE) libft/libft.a
	@$(CC) $^ -o $@
	@$(RM) $(OBJECT_TEST_FILE)

test: $(TESTS)
	./$(TESTS)
	

valgrind: re
	valgrind ./$(TARGET)
