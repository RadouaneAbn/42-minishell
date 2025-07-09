## Duplicating File Descriptors

### [n]<&word

is used to duplicate input file descriptors. If word expands to one or more digits, the file descriptor denoted by n is made to be a copy of that file descriptor. If the digits in word do not specify a file descriptor open for input, a redirection error occurs. If word evaluates to ‘-’, file descriptor n is closed. If n is not specified, the standard input (file descriptor 0) is used.

### [n]<&word
is used similarly to duplicate output file descriptors. If n is not specified, the standard output (file descriptor 1) is used. If the digits in word do not specify a file descriptor open for output, a redirection error occurs. If word evaluates to ‘-’, file descriptor n is closed. As a special case, if n is omitted, and word does not expand to one or more digits or ‘-’, the standard output and standard error are redirected as described previously.

> EXAMPLE:
```bash
# Digits in word: FD n (or default FD 0 for <& or 1 for >&) becomes a copy of FD word.

$ echo hey 1>&2 | cat -e
hey

$ echo hey | cat -e
hey$

# close FD

# close file descriptor 1
$ echo hey 1>&-
bash: echo: write error: Bad file descriptor
```

## Open File Descriptors for Reading and Writing
The redirection operator:

#### [n]<>word
shall cause the file whose name is the expansion of word to be opened for both reading and writing on the file descriptor denoted by n, or standard input if n is not specified. If the file does not exist, it shall be created.

> EXAMPLE:
```bash
$ 3<>file echo 'this will be written in file' 1>&3

$ cat file
this will be written in file

# if n is not specified. fd will be stdin
$ <>file cat -e
this will be written in file

```
