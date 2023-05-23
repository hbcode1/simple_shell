#ifndef SSHELL_H
#define SSHELL_H


/* LIBS */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>


/* helpers */

void handle_ctrl_c(int sig __attribute__((unused)));
int prmpt(void);
int newline(void);
char **split_args_by_delim(char *str, char *delim, int *n);


/* string lib */

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(char *str);

/* print to stderr*/
void putserr(char *str);
int _puterr(char c);

/* free */
void free_grid(char **grid);
void free_all(char *buff, char **grid);
#endif /* end define sshell.h header*/
