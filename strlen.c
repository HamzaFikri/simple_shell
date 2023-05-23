#include "shell.h"

/**
 * _strlen - gets the length of a string
 * @str: string to evaluate
 *
 * Return: length of string
 */

int _strlen(const char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}
