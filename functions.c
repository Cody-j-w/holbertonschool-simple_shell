#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"

char **tokenize(char *str, char *delim)
{
    size_t buffsize = 512;
    char *temp = malloc(buffsize * sizeof(char));
    char *tokens[1024];

    if (str == NULL)
    {
        exit(1);
    }


}

