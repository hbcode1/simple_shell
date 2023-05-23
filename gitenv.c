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

char *get_environment_variable(char *variableName)
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
