### SPECIAL PARAMETERS

* Listed below are the special parameters and the values to which they shall expand. Only the values of the special parameters are listed; see <p style="color: #00FF00;">Word Expansions</p> for a detailed summary of all the stages involved in expanding words.

***<span style="color: #BD93F9">@</span>***
Expands to the positional parameters, starting from one. When the expansion occurs within double-quotes, and where <bold>field splitting</bold> (see Field Splitting) is performed, each positional parameter shall expand as a separate field, with the provision that the expansion of the first parameter shall still be joined with the beginning part of the original word (assuming that the expanded parameter was embedded within a word), and the expansion of the last parameter shall still be joined with the last part of the original word. If there are no positional parameters, the expansion of '@' shall generate zero fields, even when '@' is double-quoted.

| what is $@
"$@" expands to each individual argument passed to a script or function, preserving them as separate fields (unlike "$*", which merges them into one string).
```bash
$ set one two three

$ for word in "$@"
> do
> echo "[$word]"
> done
[one]
[two]
[three]

$ for word in "$*"
> do
> echo "[$word]"
> done
[one two three]

$ set 'one one' 'two two' 'three three'

$ for word in $@
> do
> echo "[$word]"
> done
[one]
[one]
[two]
[two]
[three]
[three]
```
"$@" inside quotes will preserve each argument as its own separate fieldone

| the expansion of the first parameter shall still be joined with the beginning part of the original word
```bash
$ set 'one' 'two' 'three'

$ for word in "hey$@hey"
> do
> echo "[$word]"
> done
[heyone]
[two]
[threehey]

# note that this will give zero arguments (not empty string) even if it is quoted
$bash

$ echo "$@"

# to demonstrate that we can use c lang:
$ cat << EOF > main.c
> #include <stdio.h>
>
> int main(int argc, char **argv)
> {
>	(void)argv;
>	printf ("number of arguments is: %d\n", argc);
> }

$ cc main.c -o main

$ ./main "$@"
number of arguments is: 1

$ ./main "$1"
number of arguments is: 2

$ ./main "$var"
number of arguments is: 2
```


***<span style="color: #BD93F9">#</span>***
Expands to the decimal number of positional parameters. The command name (parameter 0) shall not be counted in the number given by '#' because it is a special parameter, not a positional parameter.
| EXAMPLES
```bash
$ cat << EOF > script.sh
> echo $#

$ chmod +x script.sh

$ ./script.sh 1 2 3 4
4

$ ./script.sh "1 2 3 4"
1

0
```

***<span style="color: #BD93F9">?</span>***
Expands to the decimal exit status of the most recent pipeline (see Pipelines).

| EXAMPLES:
```bash
$ ls
script.sh

$ echo $?
0

$ error

$ echo $?
127
```

***<span style="color: #BD93F9">-</span>***
(Hyphen.) Expands to the current option flags (the single-letter option names concatenated into a string) as specified on invocation, by the set special built-in command, or implicitly by the shell.

| EXAMPLES:

```bash
$ echo $-
himBHs

# $- prints The current set of options in your current shell.

# himBH means following options are enabled:

# H - histexpand: when history expansion is enabled
# m - monitor: when job control is enabled
# h - hashall: Locate and remember (hash) commands as they are looked up for execution
# B - braceexpand: when brace expansion is enabled
# i - interactive: when current shell is interactive

$ cat << EOF > script.sh
> #!/bin/bash
> echo $-
hB
```
| SOURCE [hyphen special character](https://stackoverflow.com/questions/42757236/what-does-mean-in-bash)

***<span style="color: #BD93F9">$</span>***
Expands to the decimal process ID of the invoked shell. In a subshell (see Shell Execution Environment ), '$' shall expand to the same value as that of the current shell.

| EXAMPLES:
```bash
$ echo $$
580987

$ (echo $$)
580987
```
SOURCE [dollar special character](https://stackoverflow.com/questions/78493/what-does-mean-in-the-shell)

***<span style="color: #BD93F9">0</span>***
(Zero.) Expands to the name of the shell or shell script. See sh for a detailed description of how this name is derived.

|EXAMPLE:

```bash
$ echo $0
bash

$ cat script.sh
#!/bin/bash
echo $0

$ ./script.sh
script.sh

$ pwd
/home/user/bash

$ home/user/bash/script.sh
home/user/bash/script.sh

```
