# EXIT CODE

The exit status of an executed command is the value returned by the waitpid system call or equivalent function. Exit statuses fall between 0 and 255, though, as explained below, the shell may use values above 125 specially. Exit statuses from shell builtins and compound commands are also limited to this range. Under certain circumstances, the shell will use special values to indicate specific failure modes.
```bash
$ echo success

$ echo $?
0
```
For the shell’s purposes, a command which exits with a zero exit status has succeeded. A non-zero exit status indicates failure. This seemingly counter-intuitive scheme is used so there is one well-defined way to indicate success and a variety of ways to indicate various failure modes. When a command terminates on a fatal signal whose number is N, Bash uses the value 128+N as the exit status.
```bash
$ cat 
^C

$ echo $?
128
```

If a command is not found, the child process created to execute it returns a status of 127. If a command is found but is not executable, the return status is 126.
```bash
$ kajsldfjkalsdf
kajsldfjkalsdf: command not found

$ echo $?
130
```

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

The exit status is used by the Bash conditional commands (see Conditional Constructs) and some of the list constructs (see Lists of Commands).

All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure, so they may be used by the conditional and list constructs. All builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments.

The exit status of the last command is available in the special parameter $? (see Special Parameters).
