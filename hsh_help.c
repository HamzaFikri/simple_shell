#include "shell.h"

/**
 * hsh_help - help command for hsh_shell builtins
 * @arg: argument lists;
 * Return: 0 if success and 2 if failed
 */
int hsh_help(char **arg)
{
	int i, size;
	builtin table[] = {
	{"exit", hsh_exit_help},     {"env", hsh_env_help},
	{"setenv", hsh_setenv_help}, {"unsetenv", hsh_unsetenv_help},
	{"cd", hsh_cd_help},         {"history", hsh_history_help},
	{"help", hsh_help_help},     {"alias", hsh_alias_help}
	};

	if (arg[1] == NULL)
	{
		_write("help usage: help COMMAND\n    ");
		_write("Prints out useful information on builtin commands\n");
		return (0);
	}
	else
	{
		size = ARRAY_SIZE(table);
		for (i = 0; i < size; i++)
		{
			if (_str_match_strict(arg[1], table[i].name))
			{
				table[i].func();
				return (0);
			}
		}
	}
	_write("No help topics match your query (._.)\n");
	return (2);
}
/**
 * hsh_help_help - builtin help printout for help
 * Return: Always 0
 */
int hsh_help_help(void)
{
	_write("help usage: help COMMAND\n    Display helpful info about builtins\n");
	return (0);
}
