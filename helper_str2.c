#include "shell.h"

/**
 * _strdup - returns a pointer to a new string which is a duplicate
 * of string str
 * @str: string to copy
 * Return: pointer to copy of string
 */

char *_strdup(char *str)
{
	char *copy_string;
	unsigned int i, j;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		;
	i++;
	copy_string = safe_malloc(i * sizeof(char));
	j = 0;
	while (j < i)
	{
		copy_string[j] = str[j];
		j++;
	}
	return (copy_string);
}


/**
 * _strchr - returns a pointer to the first occurence of the
 * character c in the string s
 * @c: caracter to return
 * @s: string to search character
 * Return: pointer to first occurence of character c or null if not found
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	else
		return (NULL);
}

/**
 * _strlen - returns length of string
 * @s: character of string
 * Return: length of string
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
		;
	return (i);
}

/**
 * _str_match_tonull - See if two strings are matching
 * @s1: string 1
 * @s2: string 2
 * Description: Returns a match if either string reaches \0 or space
 *
 * Return: 1 if match, 0 if not match
 */
int _str_match_tonull(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (1);
	}
	if (s1[i] == '\0' || s2[i] == '\0')
		return (1);
	return (0);
}
/**
 * _atoi - convert a string to a number
 * @s: string to convert
 *
 * Return: number representation of string
 */
int _atoi(char *s)
{
	int n;

	if (s == NULL)
		return (0);
	for (n = 0; *s; s++)
		if (*s >= '0' && *s <= '9')
			n = (n * 10) + (*s - '0');
	return (n);
}
