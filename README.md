# Project 1: Shell[ing] out commands
by William Lin and Sharon Zou

## Features:
1. Reads and parses a command by semicolon
2. Forks and execs the command
3. Parent process forks waits for the child to finish
2. Exit and cd commands
3. Executes commands regardless of spaces before and after commands (but can only have one space between words in a command)
3. Reads and separates multiple commands on one line with ;.   
4. Simple redirection using > (redirecting stdout) and < (redirecting stdin) (no >> or <<)
5. Implements simple pipes

## Attempted Implementation
These were the problems we had in our shell after continuous tries:
1. Redirecting stdout prints out the output intended for the file
2. Pipe also prints out the output intended for the file
3. Multiple redirection in one command
4. Running commands with more than one space within a command

## Bugs
1. Could not get certain errors to display without the error continuously popping up throughout the program (we commented out the code for errors instead)
2. Multiple redirection < > does not work and breaks the program
3. Typing in something like "hello > one.txt" will cause the program to wait for input instead of printing an error
4. Running too many times may result in a segmentation fault due to memory overload
5. Not sure if pipe works

## Files and Functions
<b> fork.c </b>
<br/>
  `=========== void initialize(); ===========
    - inputs: nothing
    - returns: nothing
    - prints a message to let the user know that he/she has entered the shell 
   ==========================================`

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

Bugs:
      - Running too many times may result in a segmentation fault due to memory overload
      - Not sure if pipe works


Files & Function Headers:
shellfunc.c
      -  void initialize();
          - inputs: nothing
          - returns: nothing
          - prints a message to let the user know that he/she has entered the shell

      - char ** parse_args(char *line);
          - inputs: char *line
          - returns: a pointer to a array of different parts of one command

      - char ** reading();
          - inputs: command line
          - returns: the command line and parses by semicolon if necessary

      - void execute(char **args);
          - input: char ** args
          - returns: nothing
          - forks and executes commands

      - char ** parse_semi(char *line);
          - inputs: char *line
          - returns: a pointer to an array of different commands separated my semicolons

      - void redirectout(char **input, int pos);
          - inputs: char **input, int pos
          - returns: nothing
          - redirects the command from input

      - void redirectin(char **input, int pos);
          - inputs: char **input, int pos
          - returns: nothing
          - redirects the command from input

      - void piping(char **input, int pos);
          - inputs: char **input, int pos
          - returns: nothing
