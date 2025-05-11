<h3 style="color: #50FA7B">rl_clear_history</h3>
```c
void rl_clear_history (void);
```
* Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

> EXAMPLE:

```c
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Initialize Readline and History
    using_history();

    // Add some commands to history
    add_history("ls -l");
    add_history("cd /home/user");

    // Clear the history
    rl_clear_history();

    // Verify history is cleared
    if (history_length == 0) {
        printf("History cleared successfully.\n");
    } else {
        printf("History still contains %d entries.\n", history_length);
    }

    return 0;
}

```
> [SOURCE](https://docs.jade.fyi/gnu/readline/readline.html#index-rl_005fclear_005fhistory)

<h3 style="color: #50FA7B">rl_on_new_line</h3>
```c
int rl_on_new_line (void);
```
* Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

```c
void add_history (const char *string);
* Place string at the end of the history list. The associated data field (if any) is set to NULL.
```
* Place string at the end of the history list. The associated data field (if any) is set to NULL. If the maximum number of history entries has been set using stifle_history(), and the new number of history entries would exceed that maximum, the oldest history entry is removed.

<h3 style="color: #50FA7B">add_history</h3>
```c
#include <readline/history.h>

void add_history (const char *string);
```

> EXAMPLE:
```c
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	add_history("Hello World!");

	printf("number of history entries: %d\n", history_length);

	add_history("Hello World! again!!");

	printf("number of history entries: %d\n", history_length);

	rl_clear_history();

	return (0);
}
```
> [SOURCE](https://tiswww.case.edu/php/chet/readline/history.html)

```c
#include <readline/readline.h>

void rl_redisplay (void);
```
* Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

> [SOURCE](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fredisplay)

<h3 style="color: #50FA7B">rl_redisplay</h3>
```c
#include <readline/readline.h>

void **rl_redisplay (void);
```
* Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.


<h3 style="color: #50FA7B">rl_replace_line</h3>
```c
#include <readline/readline.h>

void rl_replace_line (const char *text, int clear_undo);
//undo list

enum undo_code { UNDO_DELETE, UNDO_INSERT, UNDO_BEGIN, UNDO_END }; 
```
* Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.


<h3 style="color: #50FA7B">rl_line_buffer</h3>
```c
#include <readline/readline.h>

rl_line_buffer: char *
```
* This is the line gathered so far. You are welcome to modify the contents of the line, but see Allowing Undoing. The function rl_extend_line_buffer is available to increase the memory allocated to rl_line_buffer.
