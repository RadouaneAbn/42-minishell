SOURCE_FILES = $(wildcard src/lexer/*.c) \
	$(wildcard src/parser/*.c) \
	$(wildcard src/heredoc/*.c) \
	$(wildcard src/expansion/*.c)
OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

SOURCE_FILES_2 = $(wildcard src/built_in/*.c)
OBJECT_FILES_2 = $(SOURCE_FILES_2:%.c=%.o)

UTILS_FILES = $(wildcard src/utils/*.c)
UTILS_OBJECTS = $(UTILS_FILES:%.c=%.o)

TEST_FILES = $(wildcard tests_2/*.c)
TEST_OBJECTS = $(TEST_FILES:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = include
TARGET = minishell

MINITEST = minitest

all: $(TARGET)

$(TARGET): $(OBJECT_FILES) libft/libft.a
	$(CC) $^ -o $@  -lreadline
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	$(RM) $(RM_OPTIONS) $(OBJECT_FILES) $(TEST_OBJECTS) $(UTILS_OBJECTS) $(OBJECT_FILES_2)

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

test: $(MINITEST)

$(MINITEST): $(TEST_OBJECTS) $(OBJECT_FILES_2) $(UTILS_OBJECTS) libft/libft.a
	$(CC) $^ -o $@
	./$(MINITEST)

DATE = $(shell date +%F/%H/%M)

push:
	push "automatic push (minishell hsacr) $(DATE)"
