#include "shell.h"

/**
 * num_digit - get the number of digit of an integer
 * @n: integer
 *
 * Return: the number of digit
 */
int num_digit(int n)
{
	unsigned int m;
	int len = 1;

	if (n < 0)
	{
		m = -1 * n;
		len++;
	}
	else
		m = n;
	while (m > 9)
	{
		m /= 10;
		len++;
	}
	return (len);
}

/**
 * _itoa - convert an integer to a string
 * @n: integer
 *
 * Return: a pointer to the converted char
 */
char *_itoa(int n)
{
	char *res;
	unsigned int m;
	int len = num_digit(n);

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		m = -1 * n;
		res[0] = '-';
	}
	else
		m = n;
	res[len] = '\0';
	len--;
	do {
		res[len] = (m % 10) + '0';
		m /= 10;
		len--;
	} while (m > 0);
	return (re);
}
