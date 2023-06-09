#include "shell.h"

/**
 * exec_bin -  execute a built-in command
 * @data: pointer to shell data
 *
 * Return: 0 (Sucess) 1 (Failed)
 */

int exec_bin(data_t *data)
{
	bin_t bins[] = {
		{"exit", &bin_exit},
		{"env", &bin_env},
		{"setenv", &bin_setenv},
		{"unsetenv", &bin_unsetenv},
		{"cd", &bin_cd},
	};
	unsigned int i, num_bin = sizeof(bins) / sizeof(bin_t);

	for (i = 0; i < num_bin; i++)
	{
		if (_strncmp(data->args[0], bins[i].name, _strlen(bins[i].name)) == 0)
		{
			bins[i].func(data);
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
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		perror(prog_name);
		return (126);
	}
	return (0);
}

/**
 * exec_cmd - execute a command
 * @data: pointer to shell data
 *
 */

void exec_cmd(data_t *data)
{
	pid_t pid;
	int wstatus, e_stat;
	char *prog_name = NULL, *cmd_path;

	if (!(data->args[0]))
		return;
	if (exec_bin(data) == 0)
		return;
	cmd_path = get_cmd_path(data), prog_name = get_prog_name(data);
	e_stat = check_cmd_error(cmd_path, prog_name);
	if (e_stat != 0)
	{
		free(cmd_path),	free(prog_name);
		data->status = e_stat;
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free(cmd_path), free(prog_name);
		return;
	}
	else if (pid == 0)
	{
		execve(cmd_path, data->args, data->env);
	}
	else
	{
		do {
			waitpid(pid, &wstatus, WUNTRACED);
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	data->status = wstatus / 256;
	free(prog_name), free(cmd_path);
}
