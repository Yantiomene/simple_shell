#include "shell.h"


/**
 * get_prog_name - get the program name
 * @av: argument vector of the main program
 * @cmd: command name
 *
 * Return: the program name concatenate with command
 */

char *get_prog_name(char **av, char *cmd)
{
	char *prog_name = NULL;

	prog_name = _strdup(av[0]);
	prog_name = _strcat(prog_name, ": ");
	prog_name = _strcat(prog_name, cmd);
	return (prog_name);
}

/**
 * get_cmd_path - get a path to a command
 * @av: argument vector of the main program
 * @cmd: command to get the path
 *
 * Return: a pointer to the path
 */

char *get_cmd_path(char **av, char *cmd)
{
	char *path, *path_cpy, *cmd_path, *path_token, *prog_name = NULL;
	struct stat statbuf;

	prog_name = get_prog_name(av, cmd);
	if (stat(cmd, &statbuf) == 0)
		return (cmd);
	path = _getenv("PATH");
	if (path)
	{
		path_cpy = _strdup(path);
		path_token = _strtok(path_cpy, ":");
		while (path_token)
		{
			cmd_path = malloc(_strlen(cmd) + _strlen(path_token) + 2);
			if (!cmd_path)
			{
				write(STDERR_FILENO, prog_name, _strlen(prog_name));
				write(STDERR_FILENO, " : Allocation error\n", 20);
				exit(EXIT_FAILURE);
			}
			_strcpy(cmd_path, path_token), _strcat(cmd_path, "/");
			_strcat(cmd_path, cmd), _strcat(cmd_path, "\0");
			if (stat(cmd_path, &statbuf) == 0)
			{
				free(path_cpy), free(prog_name);
				return (cmd_path);
			}
			else
				free(cmd_path), path_token = _strtok(NULL, ":");
		}
		free(path_cpy), free(prog_name);
		return (NULL);
	}
	free(prog_name);
	return (NULL);
}
