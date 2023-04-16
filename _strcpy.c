#include "shell.h"

/**
 * _strcpy - copy a string to another
 * @dest: destinationn string
 * @src: source string
 *
 * Return: the destination string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}
