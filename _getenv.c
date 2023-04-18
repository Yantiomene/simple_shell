#include "shell.h"

/**
 * _getenv - prints the copy of environ
 * @path: name of the environment variable
 *
 * Return: pointer to variable or NULL, if variable is not found.
 */
char *_getenv(const char *path)
{
	extern char **environ;
	int i;
	size_t nam_len = strlen(path);

	for (i = 0; environ[i] != NULL; i++)

		if (strncmp(path, environ[i], nam_len) == 0 && environ[i][nam_len] == '=')
		{
			return (environ[i] + nam_len + 1);
		}

		return (NULL);
}
