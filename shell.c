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
	char **args;
	int state = 1, eof;

	(void)av;
	while (state)
	{
		write(STDIN_FILENO, prompt, 8);
		line = readline(&eof);
		if (eof != -1) /* End of file*/
		{
			args = split_line(line);
			exec_cmd(av, args, env);
		}
		else
		{
			state = 0;
		}
	}
	free(line);
	free(args);
	return (0);
}
