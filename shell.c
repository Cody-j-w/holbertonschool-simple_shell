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
	char *path = NULL, *strcheck = NULL, **paths = NULL, **tokens = NULL;
	extern char **environ;

	path = get_path(environ);
	paths = tokenize(path, ":");
	if (buffer == NULL)
	{
		perror("Buffer allocation failed.");
		exit(1);
	}
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ")
		getline(&buffer, &buffsize, stdin);
		if (exit_check(buffer) == 1 || feof(stdin) != 0)
			break;
		strcheck = space_check(buffer);
		if (strcmp(strcheck, " ") == 0)
			continue;
		tokens = tokenize(buffer, " ");
		fflush(stdout);
		forkit(paths, tokens);
		free_array(tokens);
		tokens = NULL;
		free(strcheck);
		strcheck = NULL;
	}
	fflush(stdout);
	free_array(paths);
	free(buffer);
	free(strcheck);
	free(path);
	exit(0);
}
