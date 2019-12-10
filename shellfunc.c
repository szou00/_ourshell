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
  printf("Welcome to DummyShell! Type 'exit' to quit the shell.\ndummy %s$ ", cwd);
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
  char line[100];
  char *l = line;
  printf("Please enter a command: ");
  fgets(l, 50, stdin);
  *(strchr(l, '\n')) = '\0'; //get rid of ending
  printf("Your command: %s\n\n", l);
  return parse_args(l);
}

void execute(char **args){
  execvp()
}
