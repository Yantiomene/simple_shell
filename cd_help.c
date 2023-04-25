#include "shell.h"

/**
 * cd_home - changes  dir to home
 * @data: pointer to data structure
 *
 */
void cd_home(data_t *data)
{
	char pwd[PATH_MAX], *home, *pwd_val;
	char *prog_name = get_prog_name(data);

	pwd_val = getcwd(pwd, sizeof(pwd));
	if (!pwd_val)
	{
		perror(prog_name);
		free(prog_name);
		return;
	}
	home = _getenv("HOME", data);
	if (!home)
	{
		_setenv("OLDPWD", pwd_val, data);
		free(prog_name);
		return;
	}
	if (chdir(home) == -1)
	{
		perror(prog_name);
		free(prog_name);
		return;
	}
	_setenv("OLDPWD", pwd_val, data);
	_setenv("PWD", home, data);
	free(prog_name);
}

/**
 * cd_dir - changes dir to a directory
 * @data: pointer to data structure
 *
 */
void cd_dir(data_t *data)
{
	char pwd[PATH_MAX], *pwd_val, *dir;
	char *prog_name = get_prog_name(data);

	dir = data->args[1];
	pwd_val = getcwd(pwd, sizeof(pwd));
	if (!pwd_val)
	{
		perror(prog_name);
		free(prog_name);
		return;
	}
	if (chdir(dir) == -1)
	{
		perror(prog_name);
		free(prog_name);
		return;
	}
	_setenv("OLDPWD", pwd_val, data);
	_setenv("PWD", dir, data);
	free(prog_name);
}

/**
 * cd_prev - changes dir to previous dir
 * @data: pointer to data structure
 *
 */
void cd_prev(data_t *data)
{
	char pwd[PATH_MAX], *pwd_val, *oldpwd_val;
	char *prog_name = get_prog_name(data);

	pwd_val = getcwd(pwd, sizeof(pwd));
	if (!pwd_val)
	{
		perror(prog_name);
		free(prog_name);
		return;
	}
	oldpwd_val = _getenv("OLDPWD", data);
	if (!oldpwd_val)
		oldpwd_val = pwd_val;
	_setenv("OLDPWD", pwd_val, data);
	if (chdir(oldpwd_val) == -1)
		_setenv("PWD", pwd_val, data);
	else
		_setenv("PWD", oldpwd_val, data);
	pwd_val = _getenv("PWD", data);
	write(STDOUT_FILENO, pwd_val, _strlen(pwd_val));
	write(STDOUT_FILENO, "\n", 1);
	free(prog_name);
}
