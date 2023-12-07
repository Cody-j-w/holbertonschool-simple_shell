#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"

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
		if (strcmp(strcheck, " ") != 0 && strcmp(strcheck, "") != 0)
		{
			tokens = tokenize(strcheck, " ");
			fflush(stdout);
			status = forkit(paths, tokens, envp, argv[0], argc);
			free_array(tokens);
			tokens = NULL;
			if (status != 0)
				break;
		}
		free(strcheck);
		strcheck = NULL;
	}
	fflush(stdout);
	free_array(paths);
	free(buffer);
	free(strcheck);
	if (path != NULL)
		free(path);
	exit(status);
}

int path_check(char *str)
{
	if (str != NULL)
	{
		if (str[0] != '\0')
			return (1);
	}
	return (0);
}
