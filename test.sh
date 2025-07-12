#!/bin/bash

make 1> /dev/null && valgrind  --leak-check=full --show-leak-kinds=all  --suppressions=readline.supp ./minishell <<< 'ls'

