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

    if (buffer == NULL)
    {
        perror("Buffer allocation failed.");
        exit(1);
    }
    while (!feof(stdin))
    {
        printf("$ ")
    }
    free(buffer);
    exit(0);
}
