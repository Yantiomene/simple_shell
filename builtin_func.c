#include "shell.h"

/**
 * bin_exit - execute the exit command
 * @args: argument vector
 *
 */
void bin_exit(char **args __attribute__((unused)))
{
	exit(EXIT_FAILURE);
}

/**
 * bin_env - execute the env command
 * @args: argument vector
 *
 */
void bin_env(char **args __attribute__((unused)))
{
	unsigned int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
