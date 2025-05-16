the cat cmd will read the fourth heredoc

rabounou@e1r10p1:~$ cat << one << two << three << four
> first heredoc
> one
> second heredoc
> two
> third heredoc
> three
> fourth heredoc
> four
fourth heredoc

in this example all heredocs are opened but only the last one was redirected to cat cmd

================================================================================

the args between the heredocs (or any redirections) are the first command arguments

Example 1:

rabounou@e1r10p1:~$ ls << 1 -l << 2 -a
> 1
> 2
total 16856
drwx------ 44 rabounou candidates  12288 May 16 18:59  .
drwxr-xr-x  8 root     root         4096 May 16 18:51  ..
drwxr-xr-x  6 rabounou candidates    101 May 16 18:59  42-minishell
...

In this example the ls command took the others args as its own args

================================================================================

Example 2:
rabounou@e1r10p1:~/42-minishell$ ls
a.out  notes  README.md  res  src
rabounou@e1r10p1:~/42-minishell$ ls > out1 -l > out2 -a
rabounou@e1r10p1:~/42-minishell$ ls
a.out  notes  out1  out2  README.md  res  src
rabounou@e1r10p1:~/42-minishell$ cat out1 
rabounou@e1r10p1:~/42-minishell$ cat out2
total 28
drwxr-xr-x  6 rabounou candidates   125 May 16 19:06 .
drwx------ 44 rabounou candidates 12288 May 16 19:05 ..
-rw-r--r--  1 rabounou candidates     0 May 10 16:53 a.out
drwxr-xr-x  8 rabounou candidates  4096 May 15 16:43 .git
-rw-r--r--  1 rabounou candidates    14 May 10 16:48 .gitignore
drwxr-xr-x  2 rabounou candidates    36 May 16 18:59 notes
-rw-r--r--  1 rabounou candidates     0 May 16 19:06 out1
-rw-r--r--  1 rabounou candidates     0 May 16 19:06 out2
-rw-r--r--  1 rabounou candidates    31 May 15 16:07 README.md
drwxr-xr-x  3 rabounou candidates   136 May 10 16:57 res
drwxr-xr-x  3 rabounou candidates    63 May 15 17:15 src


^^^ in this example the ls redirected it's output to the last redirection, but created all the files

