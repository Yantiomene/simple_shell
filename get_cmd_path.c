#include "shell.h"


/**
 * get_prog_name - get the program name
 * @data: pointer to the data structure
 *
 * Return: the program name concatenate with command
 */

char *get_prog_name(data_t *data)
{
	char *prog_name, *count = _itoa(data->count);

	prog_name = malloc(BUFFSIZE);
	_strcpy(prog_name, data->av[0]);
	_strcat(prog_name, ": ");
	_strcat(prog_name, count);
	_strcat(prog_name, ": ");
	_strcat(prog_name, data->args[0]);
	free(count);
	return (prog_name);
}

/**
 * get_cmd_path - get a path to a command
 * @data: pointer to data structure
 *
 * Return: a pointer to the path
 */

char *get_cmd_path(data_t *data)
{
	char *path, *path_cpy, *cmd_path, *path_token;
	struct stat statbuf;
	int len;

	if (stat(data->args[0], &statbuf) == 0)
		return (data->args[0]);
	path = _getenv("PATH", data);
	if (path)
	{
		path_cpy = _strdup(path);
		path_token = _strtok(path_cpy, ":");
		while (path_token)
		{
			len = _strlen(data->args[0]) + _strlen(path_token) + 2;
			cmd_path = malloc(len);
			if (!cmd_path)
			{
				print_error(":Allocation error\n", data);
				free(path_cpy);
				return (NULL);
			}
			_strcpy(cmd_path, path_token), _strcat(cmd_path, "/");
			_strcat(cmd_path, data->args[0]), _strcat(cmd_path, "\0");
			if (stat(cmd_path, &statbuf) == 0)
			{
				free(path_cpy);
				return (cmd_path);
			}
			else
				free(cmd_path), path_token = _strtok(NULL, ":");
		}
		free(path_cpy);
		return (NULL);
	}
	return (NULL);
}
