#include "shell.h"

/**
 * _isdigit - check is a string is a number
 * @s: string to be checked
 *
 * Return: 1 (True), 0 (False)
 */
int _isdigit(char *s)
{
	unsigned int i;

	if (!s)
		return (0);
	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}
