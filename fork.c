#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include <errno.h>
#include <sys/wait.h>
/**
 * forkit - check access to executable file after setting path, then execute
 * @paths: tokenized path to check access for
 * @tokens: tokenized user input that contains command
 * @env: environment
 * @prog: name of program from command line arguments
 * @count: count for error code
 * Return: the exit status of the child process
 */
int forkit(char **paths, char **tokens, char **env, char *prog, int count)
{
	int status = 0, i = 0;
	char temp_path[128];
	int env_check = strcmp(tokens[0], "env");

	if (env_check == 0)
		return (0);
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
		prog, count, tokens[0]);
		return (127);
	}
	if (access(temp_path, X_OK) == 0)
	{
		status = execute(temp_path, tokens, env);
		if (status == 512)
			return (2);
		return (0);
	}
	else
	{
	fprintf(stderr, "%s: %d: %s: not found\n", prog, count, tokens[0]);
	return (127);
	}
}
/**
 * set_path - create executable path
 * @temp_path: built executable path
 * @paths: double pointer to array containing tokenized paths
 * @tokens: double pointer to array containing tokenized user input string
 */
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
/**
 * execute - execute command in new child process
 * @path: executable pathway to command
 * @tokens: double pointer to array containing tokenized user input string
 * @env: environment
 */
int execute(char *path, char **tokens, char **env)
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
			return (status);
		}
}
