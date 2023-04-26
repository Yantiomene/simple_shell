#include "shell.h"

/**
 * set_data - set the data structure
 * @data: pointer tot the data structure
 * @av: program argument vector
 * @env: list of envirnnement variable
 *
 */

void set_data(data_t *data, char **av, char **env)
{
	unsigned int i, len;

	data->av = av;
	data->status = 0;
	data->count = 1;
	data->args = NULL;
	data->line = NULL;

	for (len = 0; env[len]; len++)
		;
	data->env = malloc(sizeof(char *) * (len + 1));
	if (!data->env)
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": Allocation error\n", 19);
		return;
	}
	for (i = 0; i < len; i++)
		data->env[i] = _strdup(env[i]);
	data->env[i] = NULL;
}

/**
 * free_data - free space allocated for data structure
 * @data: pointer to data structure
 *
 */
void free_data(data_t *data)
{
	unsigned int i;

	for (i = 0; data->env[i]; i++)
		free(data->env[i]);
	free(data->env);
}

/**
 * _reallocd - reallocate a double pointer variable
 * @p: double pointer to the previously allocated memory
 * @len: size of the previous allocated space
 * @n_len: size of the new memory space
 *
 * Return: a double pointer to the new allocated space
 */

char **_reallocd(char **p, size_t len, size_t n_len)
{
	char **n_p;
	size_t i;

	if (!p)
		return (malloc(sizeof(char *) * n_len));
	if (len == n_len)
		return (p);
	n_p = malloc(sizeof(char *) * n_len);
	if (!n_p)
		return (NULL);
	if (n_len < len)
		len = n_len;
	for (i = 0; i < len; i++)
		n_p[i] = p[i];
	free(p);
	return (n_p);
}
