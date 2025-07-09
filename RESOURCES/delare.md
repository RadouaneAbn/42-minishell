The declare command in Bash is used to set variables and their attributes. The options -x and -g control different aspects of a variable's behavior:

# declare -x (Export to Environment)
> Purpose: Marks a variable for export to the environment, making it available to child processes (e.g., scripts or commands launched from the current shell).

### Effect:

<mark>The variable is added to the environment of subsequent child processes.</mark>

Example: If you run declare `declare -x MY_VAR="hello`, then run bash `bash -c 'echo $MY_VAR'`, the child Bash process will print hello.

Scope: The variable remains in the current shell's scope (global unless declared locally in a function).

# declare -g (Global Scope)
> Purpose: Forces a variable to have global scope, even when declared inside a function (where variables are local by default).

### Effect:

<mark>Overrides the default local scope in functions.</mark>

* Example: Inside a function, `declare -g MY_VAR="world"` ensures MY_VAR is accessible outside the function.

| EXAMPLES:
```bash
$ # for -x option
$ declare -x var=bash

$ export | grep var
declare -x var=bash

$ # for -g option
$ declare -g var=bash

$ export | grep var


$ echo $var
bash

# inside a function

$ # for -g option
$ func()
> {
> declare -x var=bash
> }

$ echo $var


$ bash -c 'echo $var'


$ # for -g option
$ func()
> {
> declare -g var=bash
> }

$ echo $var
bash

$ bach -c 'echo $var'

$ # when merge the two options the variable will be exported and global
$ func()
> {
> declare -gx var=bash
> }

$ echo $var; bash -c 'echo $var'
bash
bash

$ # -x	to make NAMEs export
$ # -g	create global variables when used in a shell function; otherwise ignored
```
