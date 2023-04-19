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
 * check_cmd_error - check if the path is null or the user have a permission
 * @cmd_path: the path to the command
 * @prog_name: program name and cmd name to handle error
 *
 * Return: 1 if there is and error and o otherwise
 */
int check_cmd_error(char *cmd_path, char *prog_name)
{
	if (!cmd_path)
	{
		write(STDERR_FILENO, prog_name, _strlen(prog_name));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		return (1);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		perror(prog_name);
		return (1);
	}
	return (0);
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
	char *prog_name = get_prog_name(av, args[0]);
	char *cmd_path = get_cmd_path(av, args[0]);

	if (exec_bin(args) == 0)
		return;
	if (check_cmd_error(cmd_path, prog_name) == 1)
	{
		free(cmd_path);
		free(prog_name);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free(cmd_path);
		free(prog_name);
		return;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, env) == -1)
		{
			perror(prog_name);
			free(cmd_path);
			free(prog_name);
			return;
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
