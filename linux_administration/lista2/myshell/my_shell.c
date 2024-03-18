#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my_shell.h"

#define DBG printf("asdf\n");

#define MAX_TOKENS 20


void tokenize(char *line, char ***tokens){

    char *token = strtok(line, " ");
    int token_count = 0;
        
    while(token != NULL){
        (*tokens)[token_count] = strdup(token);
        token_count++;
        token = strtok(NULL, " ");
    }
    (*tokens)[token_count+1] = NULL;
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
        char **tokens = malloc(sizeof(char*) * MAX_TOKENS); 
        tokenize(line, &tokens);

        lsh_launch(tokens);        

        for (int i = 0; tokens[i] != NULL; i++){
            free(tokens[i]);
        }

    }

    free(line);

    return 0;
}
