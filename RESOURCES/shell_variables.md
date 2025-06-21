# SHELL VARIABLES

* Variables shall be initialized from the environment (as defined by the Base Definitions volume of IEEE Std 1003.1-2001, Chapter 8, Environment Variables and the exec function in the System Interfaces volume of IEEE Std 1003.1-2001) and can be given new values with variable assignment commands. If a variable is initialized from the environment, it shall be marked for export immediately; see the export special built-in. New variables can be defined and initialized with variable assignments, with the read or getopts utilities, with the name parameter in a for loop, with the ${ name= word} expansion, or with other mechanisms provided as implementation extensions.

1) ENV
[UP XSI] [Option Start] The processing of the ENV shell variable shall be supported on all XSI-conformant systems or if the system supports the User Portability Utilities option. [Option End]
This variable, when and only when an interactive shell is invoked, shall be subjected to parameter expansion (see Parameter Expansion) by the shell and the resulting value shall be used as a pathname of a file containing shell commands to execute in the current environment. The file need not be executable. If the expanded value of ENV is not an absolute pathname, the results are unspecified. ENV shall be ignored if the user's real and effective user IDs or real and effective group IDs are different.

2) HOME
The pathname of the user's home directory. The contents of HOME are used in tilde expansion (see Tilde Expansion).

> EXAMPLE:
```bash
$ env | grep HOME
declare -x HOME="/home/user"
```

3) IFS 
(Input Field Separators.) A string treated as a list of characters that is used for field splitting and to split lines into fields with the read command. If IFS is not set, the shell shall behave as if the value of IFS is <space>, <tab>, and <newline>; see Field Splitting. Implementations may ignore the value of IFS in the environment at the time the shell is invoked, treating IFS as if it were not set.

> EXAMPLE:
```bash
$ echo "$IFS" | cat -et
^I$

$ string="foo bar foo:bar"

$ for i in $string; do echo "[$i] extracted"; done
[foo] extracted
[bar] extracted
[foo:bar] extracted

$ IFS=":"  && echo "$IFS" | cat -et
:$

$ for i in $string; do echo "[$i] extracted"; done
[foo bar foo] extracted
[bar] extracted

$ unset IFS  && echo "$IFS" | cat -et

# Note that, after we unset IFS, Bash processed word splitting as if IFS holds the default value.
$ for i in $string; do echo "[$i] extracted"; done
[foo] extracted
[bar] extracted
[foo:bar] extracted

>$ IFS=""

# However, if we set IFS to an empty string, then Bash will not perform any splitting operation:
$ for i in $string; do echo "[$i] extracted"; done
[foo bar foo:bar] extracted
```

> NOTE: The special shell variable IFS determines how Bash recognizes word boundaries while splitting a sequence of character strings. The default value of IFS is a three-character string comprising a space, tab, and newline

> SOURCE [IFS special variable](https://www.baeldung.com/linux/ifs-shell-variable)

4) LANG
Provide a default value for the internationalization variables that are unset or null. (See the Base Definitions volume of IEEE Std 1003.1-2001, Section 8.2, Internationalization Variables for the precedence of internationalization variables used to determine the values of locale categories.)

> EXAMPLE:
```bash
$ echo $LANG
en_US.UTF-8
```

5) LC_ALL
The value of this variable overrides the LC_* variables and LANG , as described in the Base Definitions volume of IEEE Std 1003.1-2001, Chapter 8, Environment Variables.

6)LC_COLLATE
Determine the behavior of range expressions, equivalence classes, and multi-character collating elements within pattern matching.

7)PATH
A string formatted as described in the Base Definitions volume of IEEE Std 1003.1-2001, Chapter 8, Environment Variables, used to effect command interpretation; see Command Search and Execution.

```bash
$ export | grep PATH
declare -x PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
```

8)PPID
The process ID of the shell’s parent process. This variable is readonly. (in bash yes readonly but in sh it is not)

```bash
$ PPID=1234
bash: PPID: readonly variable
```
Set by the shell to the decimal process ID of the process that invoked this shell. In a subshell (see Shell Execution Environment), PPID shall be set to the same value as that of the parent of the current shell. For example, `echo $PPID; ( echo $ PPID )` would produce the same value. This volume of IEEE Std 1003.1-2001 specifies the effects of the variable only for systems supporting the User Portability Utilities option.

```bash
$ cat script.sh
#!/bin/bash

echo $PPID

$ bash script.sh
425827

$ echo $$
425827

$ echo $PPID
75295
```

8) PS2
Each time the user enters a <newline> prior to completing a command line in an interactive shell, the value of this variable shall be subjected to parameter expansion and written to standard error. The default value is "> ". This volume of IEEE Std 1003.1-2001 specifies the effects of the variable only for systems supporting the User Portability Utilities option.

> EXAMPLE:
```bash
$ << hey
< hey

$ echo "$PS2" | cat -e
> $

$ PS2='** '

$ << hey
** hey

$ echo "$PS2" | cat -e
** $
```

9)PS4
When an execution trace ( set -x) is being performed in an interactive shell, before each line in the execution trace, the value of this variable shall be subjected to parameter expansion and written to standard error. The default value is "+ ". This volume of IEEE Std 1003.1-2001 specifies the effects of the variable only for systems supporting the User Portability Utilities option.

```bash
$ echo $PS4
+
```

```txt
PS1    The  value  of  this parameter is expanded (see PROMPTING below)
       and used as the primary prompt string.   The  default  value  is
       ``\s-\v\$ ''.
PS2    The  value of this parameter is expanded as with PS1 and used as
       the secondary prompt string.  The default is ``> ''.
PS3    The value of this parameter is used as the prompt for the select
       command (see SHELL GRAMMAR above).
PS4    The  value  of  this  parameter  is expanded as with PS1 and the
       value is printed before each command  bash  displays  during  an
       execution  trace.  The first character of PS4 is replicated mul‐
       tiple times, as necessary, to indicate multiple levels of  indi‐
       rection.  The default is ``+ ''.
```

10)PWD
Set by the shell to be an absolute pathname of the current working directory, containing no components of type symbolic link, no components that are dot, and no components that are dot-dot when the shell is initialized. If an application sets or unsets the value of PWD , the behaviors of the cd and pwd utilities are unspecified.

> EXAMPLE:
```bash
$ echo $PWD

$ cd /

$ echo $PWD
/
```
