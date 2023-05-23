#include "shell.h"

/**
 * _strcmp - This program compares two strings
 * @s1:First string
 * @s2: Second string
 *
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int tot;

	if (s1 == NULL || s2 == NULL)
		return (0);

	while (*s1 && *s2)
	{
		tot = *s1 - *s2;

		if (tot != 0)
			break;
		s1++;
		s2++;
	}
	return (tot);

}
