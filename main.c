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
  // printf("Testing parse_args for 'ls -a -l'\n");
  // char *line = malloc(256);
  // strcat(line, "ls -a -l");
  // char ** args = parse_args(line);
  // printf("Printing arguments\n");
  // int i = 0;
  // while (args[i] != NULL){
  //   printf("%s\n", args[i]);
  //   i++;
  // }
  // printf("\nTesting execvp\n");
  // execvp(args[0], args);
  // while(1){
  //   initialize();
  //   break;
  // }
  // int f, p, status;
  // f = fork();
  // int e;
  // char ** args = reading();
  // if (f) { //should be the parent
  //   // printf("p: %d status: %d\n", p, status);
  //   e = 1;
  //   while (e) {
  //     p = wait(&status);
  //     if (strcmp(args[0], "exit") == 0) {
  //       e = 0;
  //     }
  //     args = reading();
  //   }
  //   printf("parent. post-fork. pid: %d parent: %d f: %d\n", getpid(), getppid(), f);
  // }
  // else {
  // //   int *q;
  // //   *q = 19;
  //   printf("child. post-fork. pid: %d parent: %d f: %d\n", getpid(), getppid(), f);
  //   execvp(args[0],args);
  //   exit(0);
  // }
  return 0;
}
