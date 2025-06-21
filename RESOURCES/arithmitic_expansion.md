#### Arithmetic Expansion

Arithmetic expansion provides a mechanism for evaluating an arithmetic expression and substituting its value. The format for arithmetic expansion shall be as follows:

> $((_expression_))

The expression shall be treated as if it were in double-quotes, except that a double-quote inside the expression is not treated specially. The shell shall expand all tokens in the expression for parameter expansion, command substitution, and quote removal.

Next, the shell shall treat this as an arithmetic expression and substitute the value of the expression. The arithmetic expression shall be processed according to the rules given in [_Arithmetic Precision and Operations_](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap01.html#tag_01_07_02_01) , with the following exceptions:

- Only signed long integer arithmetic is required.
> EXAMPLE:

```bash
$ echo $((ls))
0

$ echo $((8.0))
bash: 8.0: syntax error: invalid arithmetic operator (error token is ".0")
```
- Only the decimal-constant, octal-constant, and hexadecimal-constant constants specified in the ISO C standard, Section 6.4.4.1 are required to be recognized as constants.

```bash
$ echo $((0xf))
15

$ echo $((010))
8
```
	
- The _sizeof_() operator and the prefix and postfix "++" and "--" operators are not required.

> NOTE:
```bash
$ a=0

$ echo $((a++))

$ echo $a
1
```

- Selection, iteration, and jump statements are not supported.

All changes to variables in an arithmetic expression shall be in effect after the arithmetic expansion, as in the parameter expansion "${x=value}".

If the shell variable _x_ contains a value that forms a valid integer constant, then the arithmetic expansions "$((x))" and "$(($x))" shall return the same value.

As an extension, the shell may recognize arithmetic expressions beyond those listed. The shell may use a signed integer type with a rank larger than the rank of **signed long**. The shell may use a real-floating type instead of **signed long** as long as it does not affect the results in cases where there is no overflow. If the expression is invalid, the expansion fails and the shell shall write a message to standard error indicating the failure.

> EXAMPLES:

```bash
$ echo $((9 * 9))
81

$ echo $((0xf * 1))
15

$ x=1 echo $((x - 1))
0

$ x=1 echo $(($x - 1))
0
```
