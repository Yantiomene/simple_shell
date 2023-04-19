#include "shell.h"

/**
 * _getenv - prints the copy of environ
 * @path: name of the environment variable
 *
 * Return: pointer to variable or NULL, if variable is not found.
 */
char *_getenv(char *path)
{
	size_t nam_len = _strlen(path), i;

	for (i = 0; environ[i] != NULL; i++)
	{
	if (_strncmp(path, environ[i], nam_len) == 0 && environ[i][nam_len] == '=')
		return (environ[i] + nam_len + 1);
	}

	return (NULL);
}
