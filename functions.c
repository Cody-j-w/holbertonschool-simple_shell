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
	char *temp = NULL;
	char **tokens = malloc(buffsize * sizeof(char *));
	int i = 0;
	int cmpcheck;

	if (str == NULL)
	{
		return (0);
	}
	if (!tokens)
	{
		perror("Error: memory allocation failed");
		exit(1);
	}

	temp = strtok(str, delim);
	while (temp != NULL)
	{
		cmpcheck = strcmp(temp, "\n");
		if (cmpcheck == 0)
			break;
		tokens[i] = strdup(temp);
		temp = strtok(0, delim);
		i++;
	}
	tokens[i] = NULL;
	i--;
	if (tokens[i][strlen(tokens[i]) - 1] == '\n')
		tokens[i][strlen(tokens[i]) - 1] = '\0';
	return (tokens);

}

char *get_path(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			return (strdup(env[i] + 5));
		}
		i++;
	}
	return (0);
}

int exit_check(char *buff)
{
	int exit = strcmp(buff, "exit\n");
	int exit_nonewline = strcmp(buff, "exit");
	if (exit == 0 || exit_nonewline == 0)
	{
		return (1);
	}
	return (0);
}

void free_array(char **array)
{
	int i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

char *space_check(char *str)
{
	int i = 0, j = 0;
	int space_count = 0;
	int nonspace = 0;
	int str_len = strlen(str);
	char *newstr = NULL;

	newstr = calloc(str_len, sizeof(char));
	if (!newstr)
	{
		perror("Memory allocation failed.");
		exit(1);
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			if (space_count == 0)
			{
				space_count++;
				newstr[j] = str[i];
				j++;
			}
		}
		else if (str[i] == '\n')
		{
			break;
		}
		else{
			space_count = 0;
			nonspace++;
			newstr[j] = str[i];
			j++;
		}
		i++;
	}
	return (newstr);
}
