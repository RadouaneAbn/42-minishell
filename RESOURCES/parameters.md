# PARAMETERS

### PARAMETERS AND VARIABLES

A parameter can be denoted by a name, a number, or one of the special characters listed in Special Parameters. A variable is a parameter denoted by a name.

A parameter is set if it has an assigned value (null is a valid value). Once a variable is set, it can only be unset by using the <span style="color: #00FF00;">unset<span> special built-in command.

### POSITIONAL ARGUMENTS 

* A positional parameter is a parameter denoted by the decimal value represented by one or more digits, other than the single digit 0. The digits denoting the positional parameters shall always be interpreted as a decimal value, even if there is a leading zero. When a positional parameter with more than one digit is specified, the application shall enclose the digits in braces (see Parameter Expansion). Positional parameters are initially assigned when the shell is invoked (see sh), temporarily replaced when a shell function is invoked (see Function Definition Command), and can be reassigned with the set special built-in command.


> EXAMPLES:

```bash
$ echo $1

$ echo $2

$ echo 'hey(){echo $1}; hey HELLO; echo $1' > file.sh

$ bash file.sh WORLD
HELLO
USER
```

> NOTE: $0 is not positional argument it refers to the name of the script or the shell

```bash
$ echo $0
bash

$ echo $00000000
bash00000000000

$ echo 'hey(){echo $0}; echo $0; hey $0' > file.sh

$ bash file.sh
file.sh
file.sh
```

> NOTE: You can reassign positional parameters using the set command:

```bash
$ echo 'hey(){echo $1}; set "file1"; echo $1; hey $1' > script.sh

$ bash script.sh HELLO
file1
file1
```



