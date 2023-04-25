#include "shell.h"

/**
 * _getenv - prints the copy of environ
 * @path: name of the environment variable
 * @data: pointer to data structure
 *
 * Return: pointer to variable or NULL, if variable is not found.
 */
char *_getenv(char *path, data_t *data)
{
	size_t nam_len = _strlen(path), i;
	char *var;

	for (i = 0; data->env[i]; i++)
	{
		var = data->env[i];
		if (_strncmp(path, var, nam_len) == 0 && var[nam_len] == '=')
			return (var + nam_len + 1);
	}

	return (NULL);
}
