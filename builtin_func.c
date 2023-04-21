#include "shell.h"

/**
 * bin_exit - execute the exit command
 * @data: poointer to shell data
 *
 */
void bin_exit(data_t *data)
{
	unsigned int e_status;
	int is_digit;
	/*int len;*/
	char *prog_name = get_prog_name(data->av, data->args[0]);

	if (data->args[1] != NULL)
	{
		e_status = _atoi(data->args[1]);
		is_digit = _isdigit(data->args[1]);
		if (!is_digit)
		{
			write(STDERR_FILENO, prog_name, _strlen(prog_name));
			write(STDERR_FILENO, ": Incorrect status value: ", 26);
			write(STDERR_FILENO, data->args[1], _strlen(data->args[1]));
			write(STDERR_FILENO, "\n", 1);
			free(prog_name);
			return;
		}
		data->status = (e_status % 256);
	}
	free(prog_name);
	exit(data->status);
}

/**
 * bin_env - execute the env command
 * @data: pointer to shell data
 *
 */
void bin_env(data_t *data)
{
	unsigned int i = 0;

	while (data->env[i])
	{
		write(STDOUT_FILENO, data->env[i], _strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
