#include "shell.h"

/**
 * exec_cmd - execute a standalone command
 * @av: argument vector of the main program
 * @args: argument vector
 * @env: array of envirronnement variable
 *
 */

void exec_cmd(char **av, char **args, char **env)
{
	pid_t pid;
	int wstatus;
	char *prog_name = NULL, *cmd_path = get_cmd_path(av, args[0]);

	prog_name = _strdup(av[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, " : No such file or directory\n", 29);
		exit(EXIT_FAILURE);
	}
	prog_name = strcat(prog_name, ": ");
	prog_name = strcat(prog_name, args[0]);
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, env) == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &wstatus, WUNTRACED);
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	free(prog_name);
	free(cmd_path);
}
