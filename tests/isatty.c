#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

int main() {
    int pid = fork();
    char *s;
    if (pid == 0)
        s = "child";
    else
        s = "parent";

    if (isatty(0))
        printf("%s: stdin: TERM\n", s);
    else
        printf("%s: stdin: NOTERM\n", s);

    if (isatty(1))
        printf("%s: stdout: TERM\n", s);
    else
        printf("%s: stdout: NOTERM\n", s);

    if (isatty(2))
        printf("%s: stderr: TERM\n", s);
    else
        printf("%s: stderr: NOTERM\n", s);
}
