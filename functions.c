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
	char **tokens = malloc((buffsize * 2) * sizeof(char));
	int i = 0;

	if (str == NULL)
	{
		exit(1);
	}
	if (!temp || !tokens)
	{
		perror("Error: memory allocation failed");
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
	if (tokens[i][strlen(tokens[i]) - 1] == '\n')
		tokens[i][strlen(tokens[i]) - 1] = '\0';
	free(temp);
	return (tokens);

}

char *get_path(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			return (env[i] + 5);
		}
		i++;
	}
	return (0);
}

int exit_check(char *buff)
{
	if (strcmp(buff, "exit\n") == 0)
	{
		return (1);
	}
	return (0);
}