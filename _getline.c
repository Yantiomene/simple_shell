#include "shell.h"

/**
 * save_line - save the line
 * @line: pointer to the line
 * @n: pointer to the size of the buffer pointed by line
 * @buf: buffer that contains the line
 * @input: size of buf
 *
 */
void save_line(char **line, size_t *n, char *buf, size_t input)
{
	if (*line == NULL || *n < input)
	{
		*n = (input > BUFFSIZE) ? input : BUFFSIZE;
		*line = buf;
	}
	else
	{
		*line = _strcpy(*line, buf);
		free(buf);
	}
}

/**
 * _getline - read a line from the stream
 * @line: pointer to the line
 * @n: pointer to the size of the buffer pointed by line
 * @stream: stream from which the line will be read
 *
 * Return: the number of character read, or -1 if error
 */
ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	ssize_t num_read, i;
	char *buf, c;
	static size_t input;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	buf = malloc(sizeof(char) * BUFFSIZE);
	if (buf == 0)
		return (-1);

	do {
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFFSIZE)
			buf = _realloc(buf, input, input + 1);
		buf[input] = c;
		input++;
	} while (c != '\n');
	buf[input] = '\0';
	save_line(line, n, buf, input);
	num_read = input;
	if (i != 0)
		input = 0;
	return (num_read);
}
