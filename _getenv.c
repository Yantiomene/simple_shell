#include "shell.h"

/**
 * var_cmp - compare the var name with env var name
 * @var_name: varaible name
 * @env_var: environnement variable
 *
 * Return: the len of var_name + 1 (equal) 0 (not equal)
 */
int var_cmp(char *var_name, char *env_var)
{
	int i, len;

	for (len = 0; env_var[len] != '='; len++)
		;
	if (_strlen(var_name) != len)
		return (0);
	for (i = 0; env_var[i] != '='; i++)
	{
		if (var_name[i] != env_var[i])
			return (0);
	}
	return (i + 1);
}

/**
 * _getenv - prints the copy of environ
 * @path: name of the environment variable
 * @data: pointer to data structure
 *
 * Return: pointer to variable or NULL, if variable is not found.
 */
char *_getenv(char *path, data_t *data)
{
	int nam_len, i;
	char *var;

	for (i = 0; data->env[i]; i++)
	{
		var = data->env[i];
		nam_len = var_cmp(path, var);
		if (nam_len)
			return (var + nam_len);
	}

	return (NULL);
}
