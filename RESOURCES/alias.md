alias foo="bar "
alias bar="echo Hello"

if you run this command:
```bash
foo foo
```

#### Here's how alias substitution would work step by step:
* foo is replaced by bar (because foo is aliased to bar ).
* Now, the command becomes bar foo. Since bar ends with a space, the shell checks the next word, which is foo.
