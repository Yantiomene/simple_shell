#include "shell.h"

/**
 * exec_bin -  execute a built-in command
 * @args: argument vector
 *
 * Return: 0 (Sucess) 1 (Failed)
 */

int exec_bin(char **args)
{
	bin_t builtins[] = {
		{"exit", &bin_exit},
		{"env", &bin_env},
	};
	unsigned int i, num_bin = sizeof(builtins) / sizeof(bin_t);

	for (i = 0; i < num_bin; i++)
	{
		if (_strncmp(args[0], builtins[i].name, _strlen(args[0])) == 0)
		{
			builtins[i].func(args);
			return (0);
		}
	}
	return (1);
}

/**
 * exec_cmd - execute a command
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

	if (exec_bin(args) == 0)
		return;
	prog_name = _strdup(av[0]);
	prog_name = strcat(prog_name, ": ");
	prog_name = strcat(prog_name, args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, prog_name, _strlen(prog_name));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		free(prog_name);
		free(cmd_path);
		return;
	}
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
