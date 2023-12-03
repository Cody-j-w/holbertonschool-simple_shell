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
void forkit(char **paths, char **tokens)
{
	pid_t cpid;
	int status;
	int i = 0;
	char temp_path[512];
        extern char **environ;
	cpid = fork();
	if (cpid == -1)
	{
		perror("forkfail");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{	
		if (access(tokens[0], X_OK) == 0)
		{
			execve(tokens[0], tokens, environ);
			exit(0);
		}
		while (paths[i] != NULL)
		{
			strcpy(temp_path, paths[i]);
			strcat(temp_path, "/");
                        strcat(temp_path, tokens[0]);
                        if (access(temp_path, X_OK) == 0)
                        {
				execve(temp_path, tokens, environ);
				exit(0);
			}
                        i++;
                }
		perror("Command not found\n");
		exit(1);
	}
	else
	{
		wait(&status);
	}
}
