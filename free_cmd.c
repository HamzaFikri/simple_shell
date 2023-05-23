#include "shell.h"

/**
 * free_cmds - This program frees the cmd array
 * @m: pointer to an array of command line
 * arguments
 *
 * Return: void
 */
void free_cmds(char **m)
{
	int index = 0;

	if (m == NULL)
		return;
	while (m[index])
	{
		free(m[index]);
		index++;
	}
	free(m);
}
