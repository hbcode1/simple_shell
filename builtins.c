#include "sshell.h"

/**
 * _exit_sh - exits the shell based on the exit code
 *
 * @status: exit status
 * @av: array of command line arguments
 *
 */

void builtin_exit(char *status, char **av, char *sh)
{
    int exit_code;

    if (status)
    {
        exit_code = _atoi(status);
        if (exit_code < 0 || !is_number(status))
        {
            _putserr(sh);
            _putserr(": 1: exit: Illegal number: ");
            _putserr(status);
		    _puterr('\n');
            exit_code = 2;
        }
    }
    else
        exit_code = 2;
    free_grid(av);
    exit(exit_code);
}

/**
 * buitin_env - prints the environment using the global variable environ
 * Return: Always 0.
 */

int builtin_env(void)
{
	/* Declare the global variable environ */
    extern char **environ; 

    int i = 0;
    while (environ[i] != NULL)
    {
        _puts(environ[i]);
		_putc('\n');
        i++;
    }
    return 0;
}
