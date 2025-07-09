=> sigle quotes: Enclosing characters in single-quotes ( '' ) shall preserve the literal value of each character within the single-quotes. A single-quote cannot occur within single-quotes.
=> double quotes: Enclosing characters in double-quotes ( "" ) shall preserve the literal value of all characters within the double-quotes, with the exception of the characters dollar sign, backquote, and backslash
examples:
	dollar sign: echo "$PWD" => /home/user
	backquote: echo "`ls`" =>  minishell.txt
	backslash: echo "\$" => $
$
	The dollar sign shall retain its special meaning introducing parameter expansion (see Parameter Expansion), a form of command substitution (see Command Substitution), and arithmetic expansion (see Arithmetic Expansion).
		example:
			echo "$PWD"
			echo "$((88 * 88))"
	The input characters within the quoted string that are also enclosed between "$(" and the matching ')' shall not be affected by the double-quotes, but rather shall define that command whose output replaces the "$(...)" when the word is expanded. The tokenizing rules in Token Recognition , not including the alias substitutions in Alias Substitution , shall be applied recursively to find the matching ')'.
	Within the string of characters from an enclosed "${" to the matching '}', an even number of unescaped double-quotes or single-quotes, if any, shall occur. A preceding backslash character shall be used to escape a literal '{' or '}'. The rule in Parameter Expansion shall be used to determine the matching '}' .

types of expansion:
parameter expansion: $VAR, ${VAR}
Command Substitution: $(command), `command`
Arithmetic Expansion: $((expression))

there is differences between $() and ``:
	first: $() can be nested: ex => echo $(echo $(date)) but `` cannot

this is not valid;
alias c=clear
hey=c
> $c 
	c: command not found

alias: alias c=clear
	alias hey=c
	c => clear
	pretty good behavoir

weird behavoir:
	alias check=ls
	alias word=.
	check word => ls .
	ls word => ls word
