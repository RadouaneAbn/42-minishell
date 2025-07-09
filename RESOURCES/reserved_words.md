# RESERVED WORDS IN SHELL
#### Reserved words are words that have special meaning to the shell; see Shell Commands. The following words shall be recognized as reserved words:

```bash
! { }
do done 
case in esac
for while until
if fi elif else then
```
##### NOTE: yes these words have the meaning like the words that are used in prog languages

##### This recognition shall only occur when none of the characters is quoted and when the word is used as:
* The first word of a command
* The first word following one of the reserved words other than case, for, or in
* The third word in a case command (only in is valid in this case)
* The third word in a for command (only in and do are valid in this case)
> EXAMPLES:
```bash
#the first word of a command
for i in 0 1

#the first word following one of the reserved words other than case, for, or in
for i in  0 1
do
#The third word in a case command (only in is valid in this case)
case something in something_else
#The third word in a for command (only in and do are valid in this case)
for i in 0..10
for x do
```
See the grammar in Shell Grammar.

##### The following words may be recognized as reserved words on some implementations (when none of the characters are quoted), causing unspecified results:

```bash
[[ ]] function select
```
Words that are the concatenation of a name and a colon ( ':' ) are reserved; their use produces unspecified results.
> EXAPLES:
```bash
$ function do_something()
{
	echo i did something
}
```
> NOTE: color (:) is a shell builtin command
```bash
$ : it does not nothing actually but alright
$ : this is like a commant; ls => this will run ls

while :; do
	echo yes
done => this is an infinte loop
```


Historically, Bourne shells didn't have true and false as built-in commands. true was instead simply aliased to :, and false to something like let 0.

: is slightly better than true for portability to ancient Bourne-derived shells. As a simple example, consider having neither the ! pipeline operator nor the || list operator (as was the case for some ancient Bourne shells). This leaves the else clause of the if statement as the only means for branching based on exit status:

if command; then :; else ...; fi
Since if requires a non-empty then clause and comments don't count as non-empty, : serves as a no-op.

Historically, Bourne shells didn't have true and false as built-in commands. true was instead simply aliased to :, and false to something like let 0.

: is slightly better than true for portability to ancient Bourne-derived shells. As a simple example, consider having neither the ! pipeline operator nor the || list operator (as was the case for some ancient Bourne shells). This leaves the else clause of the if statement as the only means for branching based on exit status:

if command; then :; else ...; fi
Since if requires a non-empty then clause and comments don't count as non-empty, : serves as a no-op.

Nowadays (that is: in a modern context) you can usually use either : or true. Both are specified by POSIX, and some find true easier to read. However there is one interesting difference: : is a so-called POSIX special built-in, whereas true is a regular built-in.

Special built-ins are required to be built into the shell; Regular built-ins are only "typically" built in, but it isn't strictly guaranteed. There usually shouldn't be a regular program named : with the function of true in PATH of most systems.

Probably the most crucial difference is that with special built-ins, any variable set by the built-in - even in the environment during simple command evaluation - persists after the command completes, as demonstrated here using ksh93:

```bash
$ unset x; ( x=hi :; echo "$x" )
hi
$ ( x=hi true; echo "$x" )

$
```
Note that Zsh ignores this requirement, as does GNU Bash except when operating in POSIX compatibility mode, but all other major "POSIX sh derived" shells observe this including dash, ksh93, and mksh.

Another difference is that regular built-ins must be compatible with exec - demonstrated here using Bash:

```bash
$ ( exec : )
-bash: exec: :: not found
$ ( exec true )
$
```
POSIX also explicitly notes that : may be faster than true, though this is of course an implementation-specific detail.
SOURCE: 

[source](https://stackoverflow.com/questions/3224878/what-is-the-purpose-of-the-colon-gnu-bash-builtin)

