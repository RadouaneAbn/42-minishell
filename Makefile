SOURCE_FILES = $(wildcard src/lexer/*.c)  $(wildcard src/parser/*.c)\
							 $(wildcard src/heredoc/*.c)  $(wildcard src/expansion/*.c)\
							 $(wildcard src/utils/*.c) $(wildcard src/pathname_expansion/*.c)\
							 $(wildcard src/tree_utils/*.c)\
							$(wildcard src/gc/*.c)
OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

GC_FILES = $(wildcard src/gc/*.c)
GC_OBJS = $(GC_FILES:%.c=%.o)

SOURCE_FILES_2 = $(wildcard src/built_in/*.c) $(wildcard src/execution/*.c)
OBJECT_FILES_2 = $(SOURCE_FILES_2:%.c=%.o)

UTILS_FILES = $(wildcard src/utils/*.c)
UTILS_OBJECTS = $(UTILS_FILES:%.c=%.o)

TEST_FILES = $(wildcard tests_2/*.c)
TEST_OBJECTS = $(TEST_FILES:%.c=%.o)

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -g 

INCLUDE = include
TARGET = minishell

MINITEST = minitest

all: $(TARGET)

$(TARGET): $(OBJECT_FILES) $(OBJECT_FILES_2) $(UTILS_OBJECTS) $(GC_OBJS) libft/libft.a
	$(CC) $^ -o $@  -lreadline
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	$(RM) $(RM_OPTIONS) $(OBJECT_FILES) $(TEST_OBJECTS) $(UTILS_OBJECTS) $(OBJECT_FILES_2)
	make clean -C libft

libft/libft.a:
	make -C libft bonus

fclean: clean
	$(RM) $(RM_OPTIONS) $(TARGET)
	make fclean -C libft

re: fclean $(TARGET)

run: $(TARGET)
	clear
	./$(TARGET)

valgrind: re
	valgrind --suppressions=readline.supp --leak-check=full  -s ./$(TARGET)


fvalgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=readline.supp -s ./$(TARGET)

test: $(MINITEST)

$(MINITEST): $(TEST_OBJECTS) $(OBJECT_FILES_2) $(UTILS_OBJECTS) libft/libft.a
	$(CC) $^ -o $@
	./$(MINITEST)

DATE = $(shell date +%F/%H/%M)

push:
	git add .
	git commit -m "automatic push (minishell $$USER_NAME) $(DATE)"
	git push
