#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void initialize(){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  printf("\n\nWelcome to DummyShell! Type 'exit' to quit the shell.\n\ndummy %s$ ", cwd);
}

char ** parse_args(char *line){
  char **store = malloc(256);
  int i = 0;
  while (line){
    store[i] = strsep(&line, " ");
    i++;
  }
  return store;
}

char ** reading(){
  char *line = malloc(256);
  printf("Please enter a command: ");
  fgets(line, 50, stdin);
  *(strchr(line, '\n')) = '\0'; //get rid of ending
  char * args = malloc(256);
  return parse_args(line);
}

void execute(char **args){
  if (fork() == 0){
    execvp(args[0], args);
  }
  else{
    wait(NULL);
  }
}
