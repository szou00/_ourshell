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
      while(com[m] != 0){
        m++;
      }
      m--;
      while (k != m){
        if (strcmp(com[k], ">") == 0){
          redirectout(com, k);
          break;
        }
        else if (strcmp(com[k], "<") == 0){
          redirectin(com, k);
          break;
        }
        else if (strcmp(com[k], "|") == 0) {
          // printf("pipe arguments: %s\n", com[k]);
          piping(com, k);
        }
        k++;
      }
      if (k == m){
        if (strcmp(com[0], "exit") == 0) {
          exit(0);
        }
        if (strcmp(com[0], "cd") == 0){
          chdir(com[1]);
        }
        else{
          execute(com);
        }
      }
      i++;
    }
  }
  return 0;
}
