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
			print_error(": Incorrect status value: ", data);
			write(STDERR_FILENO, data->args[1], _strlen(data->args[1]));
			write(STDERR_FILENO, "\n", 1);
			return;
		}
		data->status = (e_status % 256);
	}
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

/**
 * bin_setenv - set an environnement variable
 * @data: pointer to the data structure
 *
 */
void bin_setenv(data_t *data)
{
	unsigned int i;
	char *var, *val;

	if (!data->args[1] || !data->args[2])
	{
		print_error(": Usage: setenv VARIABLE VALUE\n", data);
		return;
	}
	var = data->args[1];
	val = data->args[2];
	for (i = 0; data->env[i]; i++)
	{
		if (_strncmp(data->env[i], var, _strlen(var)) == 0)
		{
			free(data->env[i]);
			data->env[i] = create_var(var, val);
			if (!data->env[i])
				print_error(": Allocation error\n", data);
			return;
		}
	}
	data->env = _reallocd(data->env, i, sizeof(char *) * (i + 2));
	data->env[i] = create_var(var, val);
	if (!data->env[i])
	{
		print_error(": Allocation error\n", data);
		return;
	}
	data->env[i + 1] = NULL;
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
		return;
	}
	for (len = 0; data->env[len]; len++)
	{
		if (_strncmp(data->env[len], var, _strlen(var)) == 0)
			pos = len;
	}
	if (pos == -1)
	{
		print_error(": ", data);
		write(STDERR_FILENO, var, _strlen(var));
		write(STDERR_FILENO, ": not an environnement variable\n", 32);
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
			new_env[i] = data->env[len];
			i++;
		}
	}
	new_env[i] = NULL;
	free(data->env[pos]);
	free(data->env);
	data->env = new_env;
}
