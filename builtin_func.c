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

	if (data->args[1] != NULL)
	{
		e_status = _atoi(data->args[1]);
		is_digit = _isdigit(data->args[1]);
		if (!is_digit)
		{
			print_error(": Illegal number: ", data);
			write(STDERR_FILENO, data->args[1], _strlen(data->args[1]));
			write(STDERR_FILENO, "\n", 1);
			data->status = 2, free(data->line);
			return;
		}
		data->status = (e_status % 256);
	}
	free(data->line);
	free(data->args);
	free_data(data);
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
	data->status = 0;
	free(data->line);
}

/**
 * bin_setenv - set an environnement variable
 * @data: pointer to the data structure
 *
 */
void bin_setenv(data_t *data)
{
	char *var, *val;

	if (!data->args[1] || !data->args[2])
	{
		print_error(": Usage: setenv VARIABLE VALUE\n", data);
		data->status = -1, free(data->line);
		return;
	}
	var = data->args[1];
	val = data->args[2];
	_setenv(var, val, data);
	data->status = 0, free(data->line);
}

/**
 * bin_unsetenv - delete an env variable
 * @data: pointer to the data structure
 *
 */

void bin_unsetenv(data_t *data)
{
	char **new_env;
	char *var = data->args[1];
	int len, i, pos = -1;

	if (!var)
	{
		print_error(": Usage: unsetenv VARIABLE\n", data);
		data->status = -1, free(data->line);
		return;
	}
	for (len = 0; data->env[len]; len++)
	{
		if (_strncmp(data->env[len], var, _strlen(var)) == 0)
			pos = len;
	}
	if (pos == -1)
	{
		print_error(": ", data), write(STDERR_FILENO, var, _strlen(var));
		write(STDERR_FILENO, ": not an environnement variable\n", 32);
		data->status = -1;
		return;
	}
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
	{
		print_error(": Allocation error\n", data);
		return;
	}
	for (len = i = 0; data->env[len]; len++)
	{
		if (len != pos)
		{
			new_env[i] = data->env[len], i++;
		}
	}
	new_env[i] = NULL;
	free(data->env[pos]), free(data->env);
	data->env = new_env, data->status = 0, free(data->line);
}

/**
 * bin_cd - executes the cd command
 * @data: pointer to data structure
 *
 */
void bin_cd(data_t *data)
{
	char *dir = data->args[1];
	int is_h, is_h1;

	if (dir)
	{
		is_h = _strncmp("$HOME", dir, _strlen(dir));
		is_h1 = _strncmp("~", dir, _strlen(dir));

	}

	if (!dir || !is_h || !is_h1)
	{
		cd_home(data);
		free(data->line);
		return;
	}
	if (_strncmp("-", dir, _strlen(dir)) == 0)
	{
		cd_prev(data);
		free(data->line);
		return;
	}
	cd_dir(data), free(data->line);
}
