Project 1: Shell[ing] out commands

by William Lin and Sharon Zou

Features:
      - Reads a command
      - Parses multiple commands by semicolon
      - Forks and executes commands
      - Can execute commands regardless of spaces before and after commands (but can only have one space between words in a command)
      - Exit and cd commands
      - Simple redirection using > (redirecting stdout) and < (redirecting stdin)

Attempted:
      - The following did not end up working, but have been left in the code, commented out.
      - Attempted to run commands even with more than one space within a command
      - Continuing the shell after redirection
      - Debugging the implementation for pipes

Bugs:


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
