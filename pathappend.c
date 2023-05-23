#include "shell.h"

/**
 * pathappend - concatenates a path token with a cmd token
 * @path: path string to append to
 * @cmd: command string to append
 *
 * Return: buffer to appended path
 */

char *pathappend(char *path, char *cmd)
{
	char *buffer;
	size_t a = 0, b = 0;

	if (cmd == 0)
		cmd = "";
	if (path == 0)
		path = "";
	buffer = malloc(sizeof(char) * _strlen(path) + _strlen(cmd) + 2);
	if (buffer == NULL)
		return (NULL);
	while (path[a])
	{
		buffer[a] = path[a];
		a++;
	}
	if (path[a - 1] != '/')
	{
		buffer[a] = '/';
		a++;
	}
	while (cmd[b])
	{
		buffer[a + b] = cmd[b];
		b++;
	}
	buffer[a + b] = '\0';

	return (buffer);
}
