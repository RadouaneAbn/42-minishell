2.9.4 Compound Commands
The shell has several programming constructs that are "compound commands", which provide control flow for commands. Each of these compound commands has a reserved word or control operator at the beginning, and a corresponding terminator reserved word or operator at the end. In addition, each can be followed by redirections on the same line as the terminator. Each redirection shall apply to all the commands within the compound command that do not explicitly override that redirection.

Grouping Commands
The format for grouping commands is as follows:

(compound-list)
Execute compound-list in a subshell environment; see Shell Execution Environment. Variable assignments and built-in commands that affect the environment shall not remain in effect after the list finishes.
{ compound-list;}
Execute compound-list in the current process environment. The semicolon shown here is an example of a control operator delimiting the } reserved word. Other delimiters are possible, as shown in Shell Grammar; a <newline> is frequently used.

Key Takeaway
Compound command = Structure (e.g., if, while, { ... }).

Compound list = Commands inside the structure.


```bash
$ case echo in $(echo echo)) echo yes;;

```
