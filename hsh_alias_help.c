#include "shell.h"

/**
 * hsh_alias_help - builtin help printout for alias
 * Return: Always 0
 */
int hsh_alias_help(void)
{
	_write("alias usage: alias [KEY][=VALUE]\n    Allows aliases to be set for");
	_write(" quicker shell usage.\nAlias with no KEY VALUE prints a list of ");
	_write("aliases.\nAlias with KEY prints the alias match for that key.\n");
	_write("Alias with KEY VALUE sets or overwrites the KEY with new VALUE.\n");
	return (0);
}
