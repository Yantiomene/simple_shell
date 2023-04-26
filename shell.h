#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <ctype.h>
#include <malloc.h>
#include <signal.h>

extern char **environ;
#define BUFFSIZE 1024

/**
 * struct sh_data - structure to store shell data
 * @av: program argument vector
 * @args: argument vector
 * @env: environnement list
 * @line: input line
 * @status: exit status of a command
 * @count: the counter of command
 */
typedef struct sh_data
{
	char **av;
	char **args;
	char **env;
	char *line;
	int status;
	int count;
} data_t;

/**
 * struct builtin - structure to handle builtin command
 * @name: command name
 * @func: pointer to the function associated
 */

typedef struct builtin
{
	char *name;
	void (*func)(data_t *data);
} bin_t;

/* Built-in function */
void bin_exit(data_t *data);
void bin_env(data_t *data);
void bin_setenv(data_t *data);
void bin_unsetenv(data_t *data);
void bin_cd(data_t *data);

/* memory function */
void _memcpy(void *new_ptr, const void *ptr, size_t len);
void *_realloc(void *ptr, size_t len, size_t new_len);
char **_reallocd(char **p, size_t len, size_t n_len);

/* string functions */
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *des, char *src);
int _strlen(char *s);
char *_strdup(const char *str);
char *_strcat(char *s1, char *s2);
char *_strtok(char *str, char *sep);
int _isdigit(char *s);
int _atoi(char *s);
char *_itoa(int n);

/* data function */
void set_data(data_t *data, char **av);
void free_data(data_t *data);

/* cd functions */
void cd_home(data_t *data);
void cd_dir(data_t *data);
void cd_prev(data_t *data);

ssize_t _getline(char **line, size_t *n, FILE *stream);
void save_line(char **line, size_t *n, char *buf, size_t input);

char *readline(int *eof);
char **split_line(char *line);
char *get_cmd_path(data_t *data);
char *get_prog_name(data_t *data);
void exec_cmd(data_t *data);
int check_cmd_error(char *cmd_path, char *prog_name);
int exec_bin(data_t *data);
char *_getenv(char *path, data_t *data);
char *create_var(char *var, char *val);
void print_error(char *msg, data_t *data);
void _setenv(char *var, char *val, data_t *data);
int num_digit(int n);
void get_sigint(int sig);

#endif
