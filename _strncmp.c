#include "shell.h"
/**
 * _strncmp - compare the first n characters of a 2 strings
 * @s1: first string
 * @s2: second string
 * @n: number of character to be compared
 *
 * Return: return a number less, equal or greater than 0;
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i, res = 0;

	for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			res += s1[i] - s2[i];
			break;
		}
	}
	return (res);
}
