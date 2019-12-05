#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args(char * line) {
  int i = 0;
  char **p = malloc(5*sizeof(char));

  while (line != NULL) {
    p[i] = strsep(&line, " ");
    i++;
  }
  p[i] = NULL;
  return p;
}

char ** reading() {

  char line[100];
  char *l = line;

  printf("Please enter a command: ");
  fgets(l, 50, stdin);
  *(strchr(l, '\n')) = '\0'; //get rid of ending
  printf("Your command: %s\n\n", l);

  return parse_args(l);
}


int main(int argc, char *argv[]) {

  int f, p, status;
  printf("pre-fork\n");
  f = fork();
  int e;
  char ** args = reading();

  if (f) { //should be the parent
    // printf("p: %d status: %d\n", p, status);

    e = 0;

    while (!e) {
      p = wait(&status);
      printf("parent waiting for child\n");

      if (strcmp(args[0], "exit") == 0) {
        e = 1;
      }
      args = reading();
    }

    printf("parent. post-fork. pid: %d parent: %d f: %d\n", getpid(), getppid(), f);




  }
  else {
  //   int *q;
  //   *q = 19;
    printf("child. post-fork. pid: %d parent: %d f: %d\n", getpid(), getppid(), f);
    execvp(args[0],args);
    exit(0);

  }

}
