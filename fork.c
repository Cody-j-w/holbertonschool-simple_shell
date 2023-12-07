#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include <errno.h>
#include <sys/wait.h>
/**
 *
 *
 */
void forkit(char **paths, char **tokens, char **env, char *prog, int count)
{
	int i = 0;
	char temp_path[128];

	if (access(tokens[0], X_OK) == 0)
	{
		strcpy(temp_path, tokens[0]);
		i = 100;
	}
	if (i != 100 && paths != NULL)
	{
		set_path(temp_path, paths, tokens);
	}
	else if (i != 100 && paths == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
		prog, count, tokens[0])
		exit(127);
	}
	if (access(temp_path, X_OK) == 0)
	{
		execute(temp_path, tokens, env);
	}
	else
	{
	fprintf(stderr, "%s: %d: %s: not found\n", prog, count, tokens[0]);
	exit(127);
	}
}
void set_path(char *temp_path, char **paths, char **tokens)
{
	int i = 0;

	while (paths[i] != NULL)
	{
		strcpy(temp_path, paths[i]);
		strcat(temp_path, "/");
		strcat(temp_path, tokens[0]);
		if (access(temp_path, X_OK) == 0)
			break;
		i++;
	}
}

void execute(char *path, char **tokens, char **env)
{
	pid_t cpid;
	int status;

	cpid = fork();
		if (cpid < 0)
		{
			perror("");
			exit(1);
		}
		else if (cpid == 0)
		{
			execve(path, tokens, env);
			exit(0);
		}
		else
		{
			wait(&status);
		}
}
