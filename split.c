#include "shell.c"

/**
 * split_line - parse the input line
 * @line: line to be parsed
 *
 * Return: array of strings
 */

char **split_line(char **line)
{
	char *line_cpy, *token, *sep = " \t\n\r\a";
	char **args;
	int num_tokens, i = 0;

	line_cpy = _strdup(line);
	token = strtok(line_cpy, sep);

	while (token)
	{
		num_token++;
		token = strtok(NULL, sep);
	}

	args = malloc(sizeof(char *) * num_token);
	if (args == NULL)
	{
		write(STDERR_FILENO, "Yosh: Allocation error\n", 23);
		return (NULL);
	}

	token = strtok(line, sep);
	for (; i < num_token; i++)
	{
		args[i] = token;
		token = strtok(NULL, sep);
	}
	free(line_cpy);
	return (args);
}
