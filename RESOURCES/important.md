AND Lists
The control operator "&&" denotes an AND list. The format shall be:

command1 [ && command2] ...

First command1 shall be executed. If its exit status is zero, command2 shall be executed, and so on, until a command has a non-zero exit status or there are no more commands left to execute. The commands are expanded only if they are executed.

Exit Status
The exit status of an AND list shall be the exit status of the last command that is executed in the list.

The control operator "||" denotes an OR List. The format shall be:

command1 [ || command2] ...

First, command1 shall be executed. If its exit status is non-zero, command2 shall be executed, and so on, until a command has a zero exit status or there are no more commands left to execute.
