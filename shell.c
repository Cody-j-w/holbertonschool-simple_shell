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
            break;

        tokens = tokenize(buffer, " ");
        fflush(stdout);
        forkit(paths, tokens);
    }
    fflush(stdout);
    if (path != NULL)
        free(path);
    if (paths != NULL)
        free(paths);
    if (buffer != NULL)
        free(buffer);
    if (tokens != NULL)
        free(tokens);
    exit(0);
}
