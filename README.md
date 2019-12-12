# Project 1: Shell[ing] out commands

## Successful Implementation

Our shell so far implements the following:
1. Reading a line at a time and parsing it to separate the command from its arguments. It then forks and execs the command. The parent process waits for the exec'd program to exit before reading the next command.
2. Exit and cd commands
3. Reading and separating multiple commands on one line with ;.   
4. Simple redirection using > (redirecting stdout) and < (redirecting stdin)

## Attempted Implementation
We are currently still working on:
1. Continuing the shell after redirection
2. Debugging the implementation for pipes

## Bugs

## Function Headers
-  `void initialize();`
- `char ** parse_args(char *line);`
- `char ** reading();`
- `void execute(char **args);`
- `char ** parse_semi(char *line);`
- `int redirectout(char **input, int pos);`
- `int redirectin(char **input, int pos);`
- `void piping(char **input, int pos);`
