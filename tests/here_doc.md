```bash
$ cat << eof < /dev/stdin
> hey
> eof

$ ls && << eof
> hey
> eof
file1 file2 file3

$
```

| NOTE: < /dev/stdin → Redirects stdin to /dev/stdin. Since redirections are processed sequentially, /dev/stdin will be the last stdin file which is the heredoc.


```txt
The behavior you're seeing is due to how input redirection and command grouping (&&) work in the shell. Let's break it down:

1. Command Execution with &&
The && operator runs commands sequentially (left to right). The second command (head -n2) only executes after the first command (cat -e) finishes.

2. Input Redirection (< file.txt)
The input redirection < file.txt applies to the entire grouped command (cat -e && head -n2). Both cat and head read from the same input stream (file.txt).

3. Why head Doesn't Show Output
cat -e reads the entire file first (it reads until the end of file.txt), so the input stream is "consumed."

head -n2 then tries to read from the same input stream, but the stream is already at the end of the file (no data left).
→ head has nothing to process, so it outputs nothing.

Example Demonstration
If file.txt contains:

Line 1
Line 2
Line 3
Running (cat -e && head -n2) < file.txt:

cat -e reads the entire file and outputs:

Line 1$
Line 2$
Line 3$
(The -e flag in cat appends $ to mark line endings.)

head -n2 then runs, but there's no input left. It outputs nothing.

How to Fix This
If you want both commands to read the same input, you need to:

Reset the input stream for head, or

Duplicate the input so both commands can read from the start.

Solution 1: Use tee to duplicate the input
bash
(tee >(cat -e) | head -n2) < file.txt
Solution 2: Use separate redirections
bash
(cat -e < file.txt && head -n2 < file.txt)
Key Takeaway
Input redirection (< file.txt) binds to the entire command group.

Once cat reads the input, the stream is "empty" for subsequent commands in the group.

Use tools like tee or separate redirections to work around this.
```
