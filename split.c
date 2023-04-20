#include "shell.h"

/**
 * split_line - parse the input line
 * @line: line to be parsed
 *
 * Return: array of strings
 */

char **split_line(char *line)
{
	char *line_cpy, *token, *sep = " \t\n\r\a";
	char **args;
	int num_token = 0, i;

	line_cpy = _strdup(line);
	token = _strtok(line_cpy, sep);

	while (token)
	{
		num_token++;
		token = _strtok(NULL, sep);
	}

	args = malloc(sizeof(char *) * (num_token +1));
	if (args == NULL)
	{
		write(STDERR_FILENO, ": Allocation error\n", 19);
		return (NULL);
	}

	token = _strtok(line, sep);
	for (i = 0; i < num_token; i++)
	{
		args[i] = token;
		token = _strtok(NULL, sep);
	}
	args[i] = NULL;
	free(line_cpy);
	return (args);
}
