#include "shell.h"

/**
 * _strstr_int - finds the first occurence of the substring needle
 * in the string haystack
 * @haystack: string to search
 * @needle: string to find
 * Return: index to the beginning of the located substring
 */


int _strstr_int(char *haystack, char *needle)
{
	int i;

	i = 0;
	while (*haystack != '\0')
	{
		char *beginning = haystack;
		char *pattern = needle;

		while (*pattern == *haystack && *pattern != '\0'
			&& *haystack != '\0')
		{
			haystack++;
			pattern++;
		}
		if (*pattern == '\0')
			return (i);
		haystack = beginning + 1;
		i++;
	}
	return (-1);
}
/**
 * _strpbrk_int - Finds and returns index of first char needle in string
 * @s: haystack to search
 * @needles: Chars to search for in s
 * Return: index of first char in s, else -1
 */
int _strpbrk_int(char *s, char *needles)
{
	int i, c;

	for (i = 0; s[i]; i++)
		for (c = 0; needles[c]; c++)
			if (needles[c] == s[i])
				return (i);
	return (-1);
}
/**
 * _str_match_strict - See if two strings are matching
 * @s1: string 1
 * @s2: string 2
 * Description: Returns a match if both strings are the exactly the same
 *
 * Return: 1 if match, 0 if not match
 */
int _str_match_strict(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (1);
	}
	return (0);
}

/**
 * is_alpha - checks whether or not a char is alpha
 * @c: character to check
 * Return: 1 if true, 0 if false
 */

int is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

/**
 * is_digit - checks whether something is a digit
 * @c: character to check
 * Return: 1 if true, 0 if false
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
