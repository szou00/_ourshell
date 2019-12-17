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
      // printf("redirecting: %d\n", count_redirection(com));
      int k = 0;
      int m = 0;
      int redirected = 0;
      int piped = 0;
      while(com[m] != 0){
        m++;
      }
      m--;
      while (k != m){
        if (strcmp(com[k], ">") == 0) {
          if (redirectout(com, k)) {
            redirected = 1;
          }
        }
        else if (strcmp(com[k], "<") == 0) {
          // printf("is <\n");
          // if (count_redirection(com) == 2) {
          //   printf("double redirecting\n");
          //   double_redirecting(com, k);
          //   break;
          // }
          if (redirectin(com, k)) {
            redirected = 1;
            break;
          }
        }
        else if (strcmp(com[k], "|") == 0) {
          piped = 1;
          piping(com, k);
        }
        k++;
      }
      if (k == m && !piped && !redirected){
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
