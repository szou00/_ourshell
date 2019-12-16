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
    p = wait(&status);
  }
  else{
    if (execvp(args[0], args) == -1){
      printf("%s\n", strerror(errno));
    }
  }
  return 0;
}

int redirectout(char **input, int pos){ //">"

    // char ** input;
    // int i = 0;
    // int k = 0;
    // int doubler = 0;
    // for (i = 0; args[i] != '\0'; i++) {
    //   printf("loop\n");
    //   input[i] = args[i];
    //   if ((strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], "||") == 0) && i != k) {
    //     doubler = 1;
    //   }
    // }
    //
    // if (doubler) {
    //   char ** newInput;
    //   for (; args[i] != '\0'; i++) {
    //     input[k] = args[i];
    //     k++;
    //     printf("%s\n", input[k]);
    //   }
    // }

    int fd1 = open(input[pos + 1], O_CREAT | O_WRONLY, 0644);
    input[pos] = NULL; //so the program won't say can't be found
    if (fork() == 0) {
      dup(STDOUT_FILENO);
      dup2(fd1, STDOUT_FILENO);

      if (execvp(input[0], input) == -1){
        printf("%s\n", strerror(errno));
      }
      if(fd1 == -1){
        printf("Error: %s\n", strerror(errno));
      }

      execvp(input[0], input);
      close(fd1);

    }
    else {
      wait(NULL);
    }
  return 1;
}

int redirectin(char **input, int pos) {
  int fd1 = open(input[pos + 1], O_RDONLY);
  input[pos] = NULL;
  if (fork() == 0) {
    dup(STDIN_FILENO);
    dup2(fd1, STDIN_FILENO);

    if (execvp(input[0], input) == -1){
      printf("%s\n", strerror(errno));
    }
    if(fd1 == -1){
      printf("error: %s\n", strerror(errno));
    }

    execvp(input[0], input);
    close(fd1);
  }
  else {
    wait(NULL);
  }
  return 1;
}

void piping(char **input, int pos) {

  // int fds[2];
  // pipe(fds);

  // int i = 0;
  // char * blank = " ";
  // char command1[200] ="";
  // for (i = 0; i < pos; i++) {
  //   strcat(command1, input[i]);
  //   strcat(command1, blank);
  // }
  // char ** com_1 = parse_args(command1);
  // printf("command 1: %s\n", command1);

  // for (i = 0; i < pos; i++) {
  //   strcat(command1, input[i]);
  //   strcat(command1, blank);
  //   printf("command 1: %s\n", command1);
  // }
  char * command1;
  char * command2;

  command1 = input[pos-1];
  command2 = input[pos+1];

  char ** com_1 = parse_args(command1);
  char ** com_2 = parse_args(command2);

  // printf("command 1: %s\n", command1);
  // printf("command 2: %s\n", command2);

  input[pos] = NULL;
  char command[200];
  char line[200];

  FILE *in = popen(*com_1, "r");
  while (fgets(line,256,in)) {
      line[sizeof(line)-1] = 0;
      strcat(command,line);
  }
  pclose(in);
  FILE *out = popen(*com_2,"w");
  fprintf(out,"%s",command);
  pclose(out);


  // if (fork() == 0) {
  //
  //   dup(0);
  //   dup2(fds[1], STDOUT_FILENO);
  //   printf("command: %s\n", command1);
  //   while (read(fds[0], line, sizeof(line))) {
  //     printf("read: [%s]\n", line);
  //   }
  //   if (execvp(com_1[0], com_1) == -1) {
	// 		exit(-1);
  //   }
  //   close(fds[1]);
  // }
  //
  // else {
  //
  //   dup(0);
  //     dup2(fds[0], STDIN_FILENO);
  //     close(fds[0]);
  //     if (execvp(com_2[0], com_2) == -1) {
  // 			exit(-1);
  //     }
  //
  //
  //   wait(NULL);
  // }



}
