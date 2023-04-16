#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

ssize_t _getline(char **line, size_t *n, FILE *stream);
int _strlen(char *s);
char *_strdup(const char *str);
int main(int ac __attribute__((unused)), char **av, char **env);
char **split_line(char **line);
void exec_cmd(char **args, char **env);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);


#endif
