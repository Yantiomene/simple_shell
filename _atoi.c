#include "shell.h"

/**
 * _atoi - converts a string to integer
 * @s: string to be converted
 *
 * Return: the corresponding integer
 */
int _atoi(char *s)
{
	int res = 0, sign = 1, i = 0;

	while (s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		sign = 1 - 2 * (s[i++] == '-');
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (res > INT_MAX / 10 || (res == INT_MAX / 10 && s[i] - '0' > 7))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		res = res * 10 + s[i++] - '0';
	}
	return (res * sign);
}
