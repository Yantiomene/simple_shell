#include "shell.h"

/**
 * _strtok - parse a string folowing a seperator
 * @str: string to be parse
 * @sep: list of separator char
 *
 * Return: the token null terminated before the separator
 * On a subsequent call NULL is passed as string
 */

char *_strtok(char *str, char *sep)
{
	/* Will be used as index of the str, and keep a track on str*/
	static char *ind;
	unsigned int i;

	if (str)
		ind = str;
	else
		/* in the case of subsequent call, we commence where we left*/
		str = ind;
	if (*ind == '\0')
		return (NULL);

	while (*ind != '\0')
	{
		i = 0;
		while (sep[i])
		{
			if (*ind == sep[i])
			{
				if (ind == str)
				{
					if (!*(ind + 1))
						return (NULL);
					ind++, str++, i = 0;
					continue;
				}
				else
				{
					*ind = '\0';
					break;
				}
			} i++;
		}
		if (*ind == '\0')
		{
			ind++;
			return (str);
		} ind++;
	}
	return (str);
}
