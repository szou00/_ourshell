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
int execute(char **args){
  int f, p, status;
  f = fork();

  if (f){
    // wait(NULL);
    p = wait(&status);
    printf("---waited\n");
  }
  else{
    printf("---execing\n");
    execvp(args[0], args);
  }
  return 0;
}

<<<<<<< HEAD
void redirectout(char **input, int pos){
  int fd1 = creat(input[pos + 1], 0644);
  input[pos] = NULL;
  if (fork() == 0){
    dup2(fd1, STDOUT_FILENO);
    execvp(input[0], input);
    close(fd1);
  }
  else{
    wait(NULL);
  }
=======
int redirectout(char **input, int pos){ //">"
  // fflush(0);
  // if (fork() == 0) {
    printf("file name %s\n", input[pos + 1]); //for testing purposes
    int fd1 = creat(input[pos + 1], 0644);
    input[pos] = NULL; //so the program won't say can't be found
    dup(STDOUT_FILENO);
    printf("----duping\n");
    dup2(fd1, STDOUT_FILENO); // this line is the one giving the errors?
    printf("----duped2\n"x);
    // execute(input);
    execvp(input[0], input);
    printf("----exited\n");
    close(fd1);
  // }
  // else {
    // wait(NULL);
  // }
  // char ** args = parse_args(*input);
  return 0;
}

int redirectin(char **input, int pos) { //"<"
  // fflush(0);
  // printf("file name %s\n", input[pos + 1]);
  int fd1 = open(input[pos + 1], O_RDONLY);
  input[pos] = NULL;
  int i = 0;
  dup(STDIN_FILENO);
  dup2(fd1, STDIN_FILENO);
  close(fd1);
  execvp(input[0], input);
  close(fd1);
  return 0;
>>>>>>> f3bc852b734632e3fbc098163676384be59d242f
}

void redirectin(char **input, int pos){
  int fd0 = open(input[pos + 1], O_RDONLY, 0);
  printf("%s\n", fd0);
  int i = 0;
  char **source = malloc(256);
  while (i != pos){
    source[i] = input[i];
    i++;
  }
  if (fork() == 0){
    dup2(fd0, STDIN_FILENO);
    close(fd0);
    execvp(source[0], source);
  }
  else{
    wait(NULL);
  }
  // dup2(fd1, 1);
  // printf("%d\n", a);
  // execute(source);
  // printf("hello\n");
  // close(fd1);
}
