#include "shell.h"

/**
 * readline - read line from the stdin
 * @eof: pointer to an integer
 *
 * Return: the line just read
 */
char *readline(int *eof)
{
	char *line = NULL;
	size_t n = 0;

	*eof = getline(&line, &n, stdin);

	return (line);
}
