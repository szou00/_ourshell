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
1. Could not get certain errors to display without the error continuously popping up throughout the program
2. Multiple redirection < > does not work and breaks the program

## Files and Functions
<b> fork.c </b>
<br/>
  `void initialize();`
- Initializes the shell and prints out a line to signal user is within shell

 `char ** parse_args(char *line);`
- Input: Pointer to line
- Output: Pointer array that contains all the arguments of the command

- Parses the array by white space

  `char ** reading();`
- Input: None
- Output: Pointer to an array that contains the parsed arguments

- Reads in the command line and executes the parse functions.
- Returns the result of that.

 `void execute(char **args);`
- Input: Pointer to args
- Output: None

Runs the commands in the shell

 `char ** parse_semi(char *line);`
- Input: Pointer to line
- Output: Pointer to an array that contains all the arguments of the command

Similar to parse_args, but this function is specifically for moments when there are semicolons within the command

 `int redirectout(char **input, int pos);`
- Input: Pointer to an array of commands and an integer
- Output: 1

- Implements redirect stdout

 `int redirectin(char **input, int pos);`
- Input: Pointer to an array of commands and an integer
- Output: 1

- Implements redirect stdin

 `void piping(char **input, int pos);`
- Input: Pointer to an array of commands and an integer
- Implements simple pipes

<b> main.c </b>
- Runs the code; decides whether or not the command uses redirect or pipe

<b> funcheaders.h </b>
- Contains the function headers
