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
	char *line = NULL, *prompt = "YOsh$ ";
	char **args;
	int state = 1, eof;

	(void)av;
	do {
		write(STDOUT_FILENO, prompt, 6);
		line = readline(&eof);
		if (eof == -1) /* End of file*/
		{
			state = 0;
		}
		else
		{
			args = split_line(line);
			exec_cmd(args, env);
		}
	} while (state);
	free(line);
	free(args);
	return (0);
}
