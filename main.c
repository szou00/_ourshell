#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "funcheaders.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>



int main(int argc, char *argv[]){
  int status;
  initialize();
  printf("\n");
  while(1){
    char ** commands = reading();
    int i = 0;
    while (commands[i]){
      char **com = parse_args(commands[i]);
      int k = 0;
      int m = 0;
      int redirected = 0;
      int piped = 0;
      while(com[m] != 0){
        m++;
      }
      m--;
      while (k != m){
        // printf("argument: %s\n", com[k]);
        if (strcmp(com[k], ">") == 0) {
          // printf("redirectout\n");
          if (redirectout(com, k)) {
            redirected = 1;
            break;
          }
        }
        else if (strcmp(com[k], "<") == 0) {
          // printf("redirectin\n");
          if (redirectin(com, k)) {
            redirected = 1;
            break;
          }
        }
        else if (strcmp(com[k], "|") == 0) {
          // printf("pipe arguments: %s\n", com[k]);
          piped = 1;
          piping(com, k);
          // break;
        }
        k++;
      }
      if (k == m && !piped){
        // printf("k: %d m: %d\n", k, m);
        if (strcmp(com[0], "exit") == 0) {
          exit(0);
        }
        if (strcmp(com[0], "cd") == 0){
          chdir(com[1]);
        }
        else{
          // printf("execute\n");
          execute(com);
        }
      }
      i++;
    }
  }
  return 0;
}
