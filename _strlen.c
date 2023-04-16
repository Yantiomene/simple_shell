#include "shell.h"

/**
 * _strlen - the length of the string
 * @s: pointer to the string
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}
