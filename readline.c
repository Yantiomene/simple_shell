#include "shell.h"


/**
 * _getline -  program that displays a prompt, wait for the user to enter a command,
 * prints it on the next line
 * @line: pointer to the buffer
 * @n: size of the character
 *
 * Return: 0 if successful.
 */
ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	char *buf = NULL;
	size_t len = 0;
	ssize_t read;

	buf = malloc(sizeof(char) * len);

	if (buf == NULL)
	{
		printf("Memory allocation failed\n");
		return (0);
	}

	printf("simple_shell$ ");
	read = getline(&buf, &len, stdin); /*Read input from user*/

	if (read == -1) /*Check for end-of-file or error*/
	{
		printf("Error reading input.\n");
		return (-1);
	}

	else
	{
		printf("Command: %s", buf); /*Print the entered command*/
	}

	free(buf); /*Free the memory allocated by getline*/

	return (0);
}
