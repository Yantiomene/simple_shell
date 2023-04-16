#include "shell.h"

/**
 * exec_cmd - execute a standalone command
 * @args: argument vector
 * @env: array of envirronnement variable
 *
 */

void exec_cmd(char **args, char **env)
{
	pid_t pid;
	int wstatus;

	if (!args)
	{
		write(STDERR_FILENO, "YOsh: No such file or directory\n", 32);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Yosh");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("YOsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &wstatus, WUNTRACED);
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
}
