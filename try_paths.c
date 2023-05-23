#include "shell.h"

/**
 * try_paths - searches for PATH dir
 * containing command
 * @p: first operand
 * @cmd: second operand
 *
 * Return: unsigned int character count
 */

char *try_paths(char **p, char *cmd)
{
	int i = 0;

	char *ret;

	while (p[i])
	{
		ret = pathappend(p[i], cmd);
		if (access(ret, F_OK | X_OK) == 0)
		{
			return (ret);
		}
		else
			free(ret);
		i++;
	}
	return (NULL);
}
