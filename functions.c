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
	int i = 0;

	if (str == NULL)
	{
		exit(1);
	}

	temp = strtok(str, delim);
	while (temp != NULL)
	{
		tokens[i] = temp;
		temp = strtok(0, delim);
		i++;
	}
	tokens[i] = NULL;
	i--;
	if (tokens[i][strlen(tokens[i] - 1)] == '\n')
		tokens[i][strlen(tokens[i] - 1)] = '\0';

	return (tokens);

}
