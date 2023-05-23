#include "sshell.h"

void free_grid(char **grid)
{
	size_t i;

	if (grid)
	{
		for (i = 0; grid[i]; i++)
		{
			free(grid[i]);
		}
		free(grid);
	}
}

void free_all(char *buff, char **grid)
{
	free(buff);
	free_grid(grid);
}
