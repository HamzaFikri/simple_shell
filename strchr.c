#include "shell.h"

/**
 * _strchr - searches a string for a specific character
 * @str: string to examine
 * @chr: character to look for
 *
 * Return: pointer to index of first occurence, NULL if not found
 */

char *_strchr(char *str, int chr)
{
	while (*str)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}
