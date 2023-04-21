#include "shell.h"

/**
 * main - Checks the programs
 * @ac: argument count
 * @av: argument vector
 * @env: array of environnement var
 *
 * Return: 0 (Success)
 */

int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *line = NULL, *prompt = "(YOsh)$ ";
	data_t data;
	int state = 1, eof;

	data.av = av;
	data.env = env;
	data.status = 0;
	while (state)
	{
		write(STDIN_FILENO, prompt, 8);
		line = readline(&eof);
		if (eof != -1) /* End of file*/
		{
			data.args = split_line(line);
			exec_cmd(&data);
		}
		else
		{
			state = 0;
		}
	}
	free(line);
	free(data.args);
	return (0);
}
