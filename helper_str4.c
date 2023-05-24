#include "shell.h"

/**
 * _str_match - See if two strings are matching
 * @s1: string 1
 * @s2: string 2
 * Description: Returns a match if either string reaches \0 or space
 *
 * Return: 1 if match, 0 if not match
 */
int _str_match(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (1);
		if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
			return (1);
	}
	if (s1[i] == '\0' || s2[i] == '\0')
		return (1);
	if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
		return (1);
	return (0);
}
/**
 * string_match - Find if strings match, w multiple delims to stop the match
 * @s1: string one
 * @s2: string two
 * @delim: delimiters to stop the match on
 * Description: \0 is ALWAYS a condition to stop the match and return true.
 *				Argument 'delim' gives the function additional chars to
 *				stop the matching and return true with.
 * Return: 1 if match, 0 if no match.
 */
int string_match(char *s1, char *s2, char *delim)
{
	int i;

	if (s1 == NULL || s2 == NULL || delim == NULL)
		return (0);

	for (i = 0; s1[i] == s2[i]; i++)
		if (char_match(s1[i], delim))
			return (1);

	if (char_match(s1[i], delim) || char_match(s2[i], delim))
		return (1);

	return (0);
}
/**
 * char_match - Find if char matches any given needles
 * @c: char to match
 * @needles: string to search for matching char
 * Description: Returns true if char 'c' is a match for any character in
 *				needles, including \0. Therefore it is always a match
 *				if 'c' is \0. By design.
 * Return: 1 if match, 0 if no match.
 */
int char_match(char c, char *needles)
{
	if (needles == NULL)
		return (0);

	do {
		if (c == *needles)
			return (1);
	} while (*needles++);

	return (0);
}
