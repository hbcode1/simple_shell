#include "sshell.h"

int main(int ac, char *av[], char **env)
{
	char *buff = NULL;
	char *command = NULL;
	size_t bs = 0;
	ssize_t r = 0;
	pid_t pid;
    int status;
	(void)ac;
	signal(SIGINT, handle_ctrl_c); /* task 1 */
	/* task 1 */ while (1) 
	{
		if (isatty(STDIN_FILENO))
			prmpt();/* task 1 */
		r = getline(&buff, &bs, stdin); /* task 1 */
		if (r == -1)
		{
			if (isatty(STDIN_FILENO))
				newline();
			if (buff)
				free(buff);
			exit(EXIT_SUCCESS);
		}
		command = strtok(buff, "\n"); /* task 1 */
		pid = fork(); /* task 1 */
		if (pid == -1)
		{
			perror("Error fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
				if (execve(command,av, env) == -1)
				{
					perror(av[0]); /* task 1 */
					exit(EXIT_FAILURE);
				}
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
		buff = NULL;
	}
	return (0);
}
