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
		data->status = 2;
		return;
	}
	_setenv("OLDPWD", pwd_val, data);
	_setenv("PWD", home, data);
	free(prog_name);
	data->status = 0;
}

/**
 * check_dir - checks if a dir exists
 * @dir_name: dir name
 * @data: pointer to data structure
 *
 * Return: 1 (exists) 0 (doesn't exist) -1(failed)
 */
int check_dir(char *dir_name, data_t *data)
{
	DIR *dir = opendir(dir_name);

	if (dir)
	{
		closedir(dir);
		return (1);
	}
	if (errno == ENOENT)
	{
		print_error(": can't cd to ", data);
		write(STDERR_FILENO, dir_name, _strlen(dir_name));
		write(STDERR_FILENO, "\n", 1);
		return (0);
	}
	return (-1);
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
	if (check_dir(dir, data) == 0)
	{
		free(prog_name);
		return;
	}
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
		data->status = 2;
		return;
	}
	_setenv("OLDPWD", pwd_val, data);
	_setenv("PWD", dir, data);
	free(prog_name);
	data->status = 0;
}

/**
 * cd_prev - changes dir to previous dir
 * @data: pointer to data structure
 *
 */
void cd_prev(data_t *data)
{
	char pwd[PATH_MAX], *pwd_val, *oldpwd_val, *pwd_val_c, *oldpwd_val_c;

	getcwd(pwd, sizeof(pwd));
	pwd_val_c = _strdup(pwd);
	oldpwd_val = _getenv("OLDPWD", data);
	oldpwd_val_c = (!oldpwd_val) ? pwd_val_c : _strdup(oldpwd_val);
	_setenv("OLDPWD", pwd_val_c, data);
	if (chdir(oldpwd_val_c) == -1)
		_setenv("PWD", pwd_val_c, data);
	else
		_setenv("PWD", oldpwd_val_c, data);
	pwd_val = _getenv("PWD", data);
	write(STDOUT_FILENO, pwd_val, _strlen(pwd_val));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd_val_c);
	if (oldpwd_val)
		free(oldpwd_val_c);
	chdir(pwd_val);
	data->status = 0;
}
