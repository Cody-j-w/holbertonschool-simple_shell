#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int print_digit(int);
/**
 * main - Entry point
 *
 * Return: 0 on success, error code otherwise
 */
int main(void)
{
	size_t buffsize = 1024;
	char *buffer = malloc(buffsize * sizeof(char));
	char *str_temp;
	char *tokens[1024];
	int i = 0;
	int status;
	pid_t mypid;
	pid_t cpid;
	char *path;
	char *paths[1024];
	char *temp_path = malloc(buffsize * sizeof(char));
	char *command = malloc(32 * sizeof(char));
	extern char **environ;

	strcpy(command, "/");
	mypid = getpid();
	printf("process id: %d\n", mypid);
	
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			printf("%s\n", path);
		}
		i++;
	}
	i = 0;
	str_temp = strtok(path, ":");
	while (str_temp != NULL)
	{
		paths[i] = str_temp;
		str_temp = strtok(0, ":");
		i++;
	}
	i = 0;
	str_temp = NULL;
	
	if (buffer == NULL)
	{
		perror("Buffer allocation failed.");
		exit(1);
	}
	while (!feof(stdin))
	{
		printf("command: %s\n", command);
		printf("buffer: %s\n", buffer);
		printf("path: %s\n", path);
		printf("$: ");
		getline(&buffer, &buffsize, stdin);
		str_temp = strtok(buffer, " ");

		while (str_temp != NULL)
		{
			tokens[i] = str_temp;
			str_temp = strtok(0, " ");
			i++;
		}
		tokens[i] = NULL;
		i--;
		tokens[i][strlen(tokens[i]) - 1] = '\0';
		printf("%s\n", tokens[i]);
		strcat(command, tokens[0]);
		i = 0;
		cpid = fork();
		if (cpid == 0)
		{
		while (paths[i] != NULL)
		{
			strcpy(temp_path, paths[i]);
			strcat(temp_path, command);
			if (access(temp_path, X_OK) == 0)
			{
				execve(temp_path, tokens, environ);
				exit(1);
			}
			else
			{
				strerror(errno);
			}
			i++;
		}
		}
		else
		{
			wait(&status);
		}
		strcpy(command, "/");	
	}
	free(buffer);
	free(temp_path);
	free(command);
	

	return (0);
}

