#include "sshell.h"

char *get_environment_variable_value(char *variable, int index)
{
	if (variable)
	{
		while (index + 1)
		{
			variable++;
			index--;
		}
		return (variable);
	}
	return (NULL);
}

char* get_environment_variable(char* variableName)
{
	int index = 0, charIndex = 0;

	if (*variableName)
	{
		while (__environ[index])
		{
			while (charIndex < _strlen(variableName))
			{
				if (*(variableName + charIndex) == *(__environ[index] + charIndex))
					charIndex++;
				else
				{
					charIndex = 0;
					index++;
				}
			}
			if (charIndex == _strlen(variableName))
				return (get_environment_variable_value(__environ[index], charIndex));
			charIndex = 0;
			index++;
		}
	}
	return (NULL);
}
char **get_directories(char *path) {
    int num_directories = 0;
    char **directories;

    directories = split_args_by_delim(path, ":", &num_directories);

    return (directories);
}

char *search_command_in_path(char *command, char *search_path)
{
	unsigned int index;
	struct stat file_stats;
	char **directories;
	char *command_path;

	index = 0;
	directories = get_directories(search_path);
	while (directories[index])
	{
		command_path = malloc((_strlen(directories[index]) +
							   _strlen(command) + 2) * sizeof(char));
		if (!command_path)
			return (command_path);
		_strcpy(command_path, directories[index]);
		_strcat(command_path, "/");
		_strcat(command_path, command);
		_strcat(command_path, "\0");
		if (stat(command_path, &file_stats) == 0)
		{
			return (command_path);
		}
		free(command_path);
		index++;
	}
	return (NULL);
}

int is_valid_command(char *command)
{
	struct stat command_stats;

	if (!*command)
		return (1);
	if (stat(command, &command_stats) == 0)
	{
		return (0);
	}
	return (1);
}
char *locate_command(char *command_name) {
    char *path = NULL;
    char *path_found = NULL;

    if (command_name != NULL) {
        if (is_valid_command(command_name)) {
            path = get_environment_variable("PATH");
            if (path != NULL) {
                path_found = search_command_in_path(command_name, path);
            }
            if (path_found != NULL) {
                return (path_found);
            }
        }
        return (command_name);
    }
    return (NULL);
}
