#include "shell.h"

/**
 * main - Checks the programs
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 (Success)
 */

int main(int ac __attribute__((unused)), char **av)
{
	char *prompt = "(YAsh)$ ";
	data_t data;
	int state = 1, eof;

	signal(SIGINT, get_sigint);
	set_data(&data, av);
	while (state)
	{
		write(STDIN_FILENO, prompt, 8);
		data.line = readline(&eof);
		if (eof != -1) /* End of file*/
		{
			data.args = split_line(data.line);
			exec_cmd(&data);
			data.count += 1;
			if (data.args)
				free(data.args);
		}
		else
		{
			state = 0;
		}
	}
	if (data.line)
		free(data.line);
	free_data(&data);
	return (data.status);
}
