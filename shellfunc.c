#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

// Writes a message to the user to indicate that the shell is running
void initialize(){
  printf("\n\nWelcome to DummyShell! Type 'exit' to quit the shell.\n\n");
}

// Parses a line of code and splits it into valid commands
char ** parse_args(char *line){
  char **store = malloc(256);
  int i = 0;
  while (line){
    store[i] = strsep(&line, " ");
    i++;
  }
  // char **new = malloc(256);
  // int j = 0;
  // int k = 0;
  // int m = sizeof(store);
  // while (j != i){
  //   if (strcmp(store[j], " ") != 0){
  //     new[k] = store[j];
  //     k++;
  //   }
  //   j++;
  // }
  // printf("%s\n", new[2]);
  // store = new;
  return store;
}

char ** parse_semi(char *line){
  char **store = malloc(256);
  int i = 0;
  while (line){
    store[i] = strsep(&line, ";");
    int j = 0;
    while(store[i][j] == ' '){
      j++;
    }
    int k = strlen(store[i]);
    k--;
    while(store[i][k] == ' '){
      k--;
    }
    char *new = malloc(256);
    int m = 0;
    while (j != k + 1){
      new[m] = store[i][j];
      m++;
      j++;
    }
    store[i] = new;
    i++;
  }
  return store;
}

// Reads in the command line and returns the parsed version of it
char ** reading(){
  char *line = malloc(256);
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  printf("(dummy)%s$ ", cwd);
  fgets(line, 50, stdin);
  *(strchr(line, '\n')) = '\0'; //get rid of ending
  return parse_semi(line);
}

// Runs commands in the shell
void execute(char **args){
  if (fork() == 0){
    execvp(args[0], args);
  }
  else{
    wait(NULL);
  }
}

int redirectout(char **input, int pos){ //"<"
  // fflush(0);
  // printf("file name %s\n", input[pos + 1]); //for testing purposes
  int fd1 = creat(input[pos + 1], 0644);
  input[pos] = NULL; //so the program won't say can't be found
  dup(STDIN_FILENO);
  dup2(fd1, STDOUT_FILENO);
  execvp(input[0], input);
  close(fd1);
  return 0;
}

int redirectin(char **input, int pos) { //">"
  // fflush(0);
  // printf("file name %s\n", input[pos + 1]);
  int fd1 = open(input[pos + 1], O_RDONLY);
  input[pos] = NULL;
  int i = 0;
  dup(STDIN_FILENO);
  dup2(fd1, STDIN_FILENO);
  close(fd1);
  execvp(input[0], input);
  return 0;
}

void piping(char **input, int pos) { //doesn't really work yet
  FILE *in = popen(input[pos], "r");
  printf("file name %s\n", input[pos]);
  FILE *out = popen(input[pos+2], "w");
  printf("file name %s\n", input[pos + 2]);
  input[pos] = NULL;
  char line[200];
  while (fgets(line, 200, in)) {
    fputs(line, out);
  }
  pclose(in);
  pclose(out);
}
// int redirect_type(char * command){
//
// }
