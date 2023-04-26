#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @des: the first string
 * @src: the second string
 *
 * Return: the concatenated string
 */
char *_strcat(char *des, char *src)
{
	int j;
	int i;

	for (j = 0; des[j] != '\0'; j++)
		;
	for (i = 0; src[i] != '\0'; i++)
	{
		des[j] = src[i];
		j++;
	}
	des[j] = '\0';
	return (des);
}
