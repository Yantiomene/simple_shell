#include <shell.h>

/**
 * _strcat - concatenates two strings
 * @des: the first string
 * @src: the second string
 *
 * Return: the concatenated string
 */
char *_strcat(char *des, char *src)
{
	int i, j;

	i = 0;
	while (des[i] != '\0')
	{
		i++;
	}

	j = 0;
	while (src[j] != '\0')
	{
		des[i] = src[j];
		i++;
		j++;
	}

	des[i] = '\0';

	return (des);
}
