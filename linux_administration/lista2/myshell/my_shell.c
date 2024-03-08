#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my_shell.h"



void tokenize(char *line, char ***tokens){

    char *token = strtok(line, " ");
    int token_count = 0;
        
    while(token != NULL){
         (*tokens)[token_count] = strdup(token);
         token_count++;
         token = strtok(NULL, " ");
    }
}

int make_process(char **tokens){
    int exit_code = -1;

    return exit_code;
}

int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


int main(int argc, char **argv){
    printf("%d\n", argc);
    
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, stdin)) != -1){
        char **tokens = malloc(sizeof(char*) * 20); 
        tokenize(line, &tokens);

        lsh_launch(tokens);        

        free(tokens);
    }

    free(line);

    return 0;
}
