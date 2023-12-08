#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - main function of shell program
 * @argc: amount of arguments passed to main from command line
 * @argv: arguments passed to main from command line
 * @envp: environment
 * Return: Exit 0 on success, exit 1 on failure
 */
int main(int argc, char *argv[], char *envp[])
{
	size_t buffsize = 1024;
	int status = 0;
	char *buffer = malloc(buffsize * sizeof(char));
	char *path = NULL, *strcheck = NULL, **paths = NULL, **tokens = NULL;

	path = get_path(envp);
	if (path_check(path) != 0)
		paths = tokenize(path, ":");
	if (buffer == NULL)
		exit(1);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		getline(&buffer, &buffsize, stdin);
		if (exit_check(buffer) == 1 || feof(stdin) != 0)
			break;
		strcheck = space_check(buffer);
		env_check(strcheck, envp);
		if (strcmp(strcheck, " ") != 0 && strcmp(strcheck, "") != 0)
		{
			tokens = tokenize(strcheck, " ");
			status = forkit(paths, tokens, envp, argv[0], argc);
			free_array(tokens);
			tokens = NULL;
			if (status != 0)
				break;
		}
		free(strcheck);
		strcheck = NULL;
	}
	free_array(paths);
	free(buffer);
	free(strcheck);
	if (path != NULL)
		free(path);
	exit(status);
}
/**
 * path_check - check validity and existence of input string
 * @str: string to check
 * Return: 0 on success, 1 on failure
 */
int path_check(char *str)
{
	if (str != NULL)
	{
		if (str[0] != '\0')
			return (1);
	}
	return (0);
}

/**
 * env_check - prints environment variables if current buffered string is "env"
 * @buff: the buffered string
 * @env: the current environment
*/

void env_check(char *buff, char **env)
{
	int i = 0;
	int check = strcmp(buff, "env");

	if (check == 0)
	{
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
