#include "shell.h"

/**
 * hsh_exit - builtin command hsh_exit, mimics exit
 * @arg_list: arg_list given by user input
 * @envp: environmental linked list
 * @buf_size: the size of path
 * Return: 0 on success;
 */
int hsh_exit(char **arg_list, env_t *envp, int buf_size)
{
	int tmp;
	(void) buf_size;

	if (arg_list[1] != NULL)
	{
		if (!(is_digit(arg_list[1][0])))
		{
			/*_write("exit: Expression Syntax.\n");*/
			return (2);
		}
	}
	tmp = _atoi(arg_list[1]);
	history_wrapper("", envp, 'w');
	defer_free(FREE_ADDRESSES);
	_exit(tmp & 0377);
	return (0);
}
/**
 * hsh_exit_help - builtin help printout for exit
 * Return: Always 0
 */
int hsh_exit_help(void)
{
	_write("exit usage: exit N\n    Exit the shell.\n\n    ");
	_write("Exits the shell with a status of N.  If N is omitted, ");
	_write("the exit status\n    is that of the last command executed.\n");
	return (0);
}
