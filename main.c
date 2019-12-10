#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funcheaders.h"



int main(int argc, char *argv[]){
  initialize();
  printf("\n");
  while(1){
    char ** commands = reading();
    if (strcmp(commands[0], "exit") == 0) {
      exit(0);
    }
    if (strcmp(commands[0], "cd") == 0){
      chdir(commands[1]);
    }
    else{
      execute(commands);
    }
  }
  return 0;
}
