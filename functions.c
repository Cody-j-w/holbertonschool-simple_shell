#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * tokenize - separate AKA tokenize a string at the given delimiter
 * @str: string to tokenize
 * @delim: delimiter in string to replace with null byte
 * Return: tokens array on success, exit on failure
 */
char **tokenize(char *str, char *delim)
{
	size_t buffsize = 512;
	char *temp = NULL;
	char **tokens = malloc(buffsize * sizeof(char *));
	int i = 0;
	int cmpcheck;

	if (str == NULL)
	{
		free(tokens);
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
/**
 * get_path - extract the path from environment
 * @env: environmental variables
 * Return: 0 on success
 */
char *get_path(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("Current env variable being checked: %s\n", env[i]);
		if (strncmp(env[i], "PATH1=", 6) == 0)
		{
			return (0);
		}
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			return (strdup(env[i] + 5));
		}
		i++;
	}
	return (0);
}
/**
 * exit_check - checks if user input is "exit"
 * @buff: buffer containing input string
 * Return: 1 if exit, 0 if no exit
 */
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
/**
 * free_array - free memory allocation of arrays
 * @array: array to be freed
 */
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
/**
 * space_check - check for and trim extra spaces and new lines
 * @str: string to check for extra spaces
 * Return: newstr on success, otherwise exit
 */
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
		else
		{
			space_count = 0;
			nonspace++;
			newstr[j] = str[i];
			j++;
		}
		i++;
	}
	return (newstr);
}
