#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *tmp;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	tmp = malloc(sizeof(char) * (len + 1));

	if (tmp = NULL)
		return (NULL);
	for (int i = 0; i <= len; i++)
		tmp[i] = str[i];
	return (tmp);
}
