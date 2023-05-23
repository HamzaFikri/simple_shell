#include "shell.h"

/**
 * token_maker - splits a string into an array of tokens
 * @str: string to be tokenized and packaged
 *
 * Return: vector array of string tokens
 */

char **token_maker(char *str)
{
	size_t idx = 0, io = 0;
	int tkn = 1;
	char **tokens = NULL;
	char *buf = NULL, *token = NULL, *bufptr = NULL, *delim = " :\t\r\n";

	buf = _strdup(str);
	if (buf == NULL)
		return (NULL);
	bufptr = buf;

	while (*bufptr)
	{
		if (_strchr(delim, *bufptr) != NULL && io == 0)
		{
			tkn++;
			io = 1;
		}
		else if (_strchr(delim, *bufptr) == NULL && io == 1)
			io = 0;
		bufptr++;
	}
	tokens = malloc(sizeof(char *) * (tkn + 1));
	token = strtok(buf, delim);
	while (token)
	{
		tokens[idx] = _strdup(token);
		if (tokens[idx] == NULL)
		{
			free(tokens);
			return (NULL);
		}
		token = strtok(NULL, delim);
		idx++;
	}
	tokens[idx] = NULL;

	free(buf);
	return (tokens);
}
