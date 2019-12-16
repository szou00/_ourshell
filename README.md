# Project 1: Shell[ing] out commands
By Sharon Zou and William Lin

## Successful Implementation

Features:
1. Reading a line at a time and parsing it to separate the command from its arguments. It then forks and execs the command. The parent process waits for the exec'd program to exit before reading the next command.
2. Exit and cd commands
3. Reading and separating multiple commands on one line with ;.   
4. Simple redirection using > (redirecting stdout) and < (redirecting stdin) (no >> or <<)
5. Implement simple pipes

## Attempted Implementation
These were the problems we had in our shell after continuous tries:
1. Redirecting stdout prints out the output intended for the file
2. Multiple redirection

## Bugs
1. Putting two ;; will cause a "Bad Address" that will follow through program
2. Multiple redirection < > do not work and breaks the program

## Function Headers
<b> fork.c </b>
-  `void initialize();`
Initializes the shell and prints out a line to signal user is within shell

- `char ** parse_args(char *line);`
Input: The command written to the shell
Output: An array that contains all the arguments of the command

Parses the array by white space

- `char ** reading();`
Input: None
Output: An array that contains the parsed arguments

Reads in the command line and executes the parse functions.
Returns the result of that.

- `void execute(char **args);`
Input: An array of arguments
Output: None

Runs the commands in the shell

- `char ** parse_semi(char *line);`
Input: The command written to the shell
Output: An array that contains all the arguments of the command

Similar to parse_args, but this function is specifically for moments when there are semicolons within the command

- `int redirectout(char **input, int pos);`
Input: An array of commands, and an integer
Output: 1

Implements redirect stdout

- `int redirectin(char **input, int pos);`
Input: An array of commands, and an integer
Output: 1

Implements redirect stdin

- `void piping(char **input, int pos);`
Input: An array of commands, and an integer
Implements simple pipes
