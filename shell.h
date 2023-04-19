#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct builtin - structure to handle builtin command
 * @name: command name
 * @func: pointer to the function associated
 */

typedef struct builtin
{
	char *name;
	void (*func)(char **args __attribute__((unused)));
} bin_t;

/* Built-in function */
void bin_exit(char **args __attribute__((unused)));
void bin_env(char **args __attribute__((unused)));

char *readline(int *eof);
int _strlen(char *s);
char *_strdup(const char *str);
char **split_line(char *line);
char *get_cmd_path(char **av, char *cmd);
void exec_cmd(char **av, char **args, char **env);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *des, char *src);
int exec_bin(char **args);
char *_strcat(char *s1, char *s2);
char *_getenv(char *path);
char *get_cmd_path(char *cmd);


#endif
