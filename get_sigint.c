#include "shell.h"

/**
 * get_sigint - Handle crtl + c
 * @sig: signal number
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n(YAsh)$ ", 9);
}
