#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funcheaders.h"
#include <fcntl.h>



int main(int argc, char *argv[]){
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
        // printf("in loop. commands, m: %d com[m]: %s\n", m, com[m]);
        m++;
      }
      // printf("out loop. commands, m: %d com[m]: %s\n", m, com[m]);
      m--;
      while (k != m){
        // printf("commands, k: %d com[k]: %s\n", k, com[k]);
        // printf("%s\n", com);
          // printf("%s\n", "testing for special character]");
          if (strcmp(com[k], ">") == 0) {
            // printf("%s\n", "OUT!"); //testing
            redirectout(com, k);
          }
          else if (strcmp(com[k], "<") == 0) {
            // printf("%s\n", "IN!");
            redirectin(com, k);
          }
          else if (strcmp(com[k], "|") == 0) {
            // printf("%s\n", "pipe!");
            piping(com, k);
          // }
          }
          else {
            k++;
          }
        // printf("m: %d, k: %d\n", m, k);
        // printf("%s\n", "still here");
      }
      if (k == m){
        // printf("%s\n", "equal");
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
