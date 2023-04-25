#include "shell.h"

/**
 * create_var - create a new env variable
 * @var: variable name
 * @val: variable value
 *
 * Return: the new env var created
 */
char *create_var(char *var, char *val)
{
	char *new_var;
	unsigned int len;

	len = _strlen(var) + _strlen(val) + 2;
	new_var =  malloc(sizeof(char) * len);
	if (!new_var)
	{
		return (NULL);
	}
	_strcpy(new_var, var);
	_strcat(new_var, "=");
	_strcat(new_var, val);
	_strcat(new_var, "\0");
	return (new_var);
}

/**
 * print_error - prints a message error to STDERR
 * @msg: message to be printed
 * @data: pointer to the data structure
 *
 */
void print_error(char *msg, data_t *data)
{
	char *prog_name = get_prog_name(data);

	write(STDERR_FILENO, prog_name, _strlen(prog_name));
	write(STDERR_FILENO, msg, _strlen(msg));
	free(prog_name);
}


/**
 * _setenv - set the env variable
 * @var: env variable name
 * @val: env variable value
 * @data: pointer to the data structure
 *
 */
void _setenv(char *var, char *val, data_t *data)
{
	unsigned int i;

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
