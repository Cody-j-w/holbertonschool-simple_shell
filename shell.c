#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"

int main(void)
{
    size_t buffsize = 1024;
    char *buffer = malloc(buffsize * sizeof(char));
    char *path = malloc(buffsize * sizeof(char));
    char **paths;
    char **tokens;
    extern char **environ;

    path = get_path(environ);
    paths = tokenize(path, ":");

    if (buffer == NULL)
    {
        perror("Buffer allocation failed.");
        exit(1);
    }
    while (!feof(stdin))
    {
        printf("$ ");
        getline(&buffer, &buffsize, stdin);
        if (exit_check(buffer) == 1)
        {
            break;
        }
        else
        {
            tokens = tokenize(buffer, " ");
            forkit(paths, tokens);
        }
    }
    free(path);
    free(paths);
    free(buffer);
    free(tokens);
    exit(0);
}
