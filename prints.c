#include "sshell.h"

int _puterr(char c)
{
	return (write(2, &c, 1));
}

int prmpt(void)
{
	write(STDERR_FILENO, "$ ", 2);
	return (0);
}

int newline(void)
{
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

void handle_ctrl_c(int sig __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
	prmpt();
}

void putserr(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_puterr(str[i]);
	}
}
