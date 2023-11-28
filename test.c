#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int print_digit(int);
/**
 * main - Entry point
 *
 * Return: 0 on success, error code otherwise
 */
int main(int argc, char *argv[])
{
	size_t buffsize = 1024;
	char *buffer = malloc(buffsize * sizeof(char));
	char *str_temp;
	char *tokens[1024];
	int i = 0;
	int characters;
	char *path;
	char *paths[1024];
	char *temp_path = malloc(buffsize * sizeof(char));
	char *command = malloc(32 * sizeof(char));
	extern char **environ;

	strcpy(command, "/");
	
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i];
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
	printf("$: ");
	characters = getline(&buffer, &buffsize, stdin);
	str_temp = strtok(buffer, " ");

	while (str_temp != NULL)
	{
		tokens[i] = str_temp;
		str_temp = strtok(0, " ");
		i++;
	}
	i--;
	tokens[i][strlen(tokens[i]) - 1] = '\0';
	printf("%s\n", tokens[i]);
	strcat(command, tokens[0]);
	i = 0;

	while (paths[i] != NULL)
	{
		strcpy(temp_path, paths[i]);
		printf("after strcpy: %s\n", temp_path);
		strcat(temp_path, command);
		if (access(temp_path, X_OK) == 0)
		{
			execve(temp_path, tokens, NULL);
		}
		else
		{
			strerror(errno);
		}
		i++;
	}
	
	

	return (0);
}

