#include "sshell.h"

int main(int ac, char *av[], char **env)
{
	char *buff = NULL;
	char *command = NULL;
	char **cmd_args = NULL; /* task 2 */
	size_t bs = 0;
	ssize_t r = 0;
	pid_t pid;
	int status, argsn = 0; /* task 2 */

	(void)ac;
	(void)av;
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
		cmd_args = split_args_by_delim(command, " ", &argsn); /* task 2 */
		pid = fork(); /* task 1 */
		if (pid == -1)
		{
			free_all(buff, cmd_args); /* task 2 */
			perror("Error fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
				if (execve(cmd_args[0], cmd_args, env) == -1) /* task 2 */
				{
					perror(cmd_args[0]); /* task 1 */
					free_all(buff, cmd_args);/* task 2 */
					exit(EXIT_FAILURE);
				}
			free_all(buff, cmd_args); /* task 2 */
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
		free_all(buff, cmd_args); /* task 2 */
		buff = NULL;
		cmd_args = NULL; /* task 2 */
	}
	free_all(buff, cmd_args); /* task 2 */
	return (0);
}
