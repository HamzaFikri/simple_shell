#include "shell.h"

/**
 * hsh_env - builtin command hsh_env, mimics sh builtin env
 * @arg_list: arguement list vectors
 * @envp: environmental variables to print
 * Return: 0 if success.
 */
int hsh_env(char **arg_list, env_t *envp)
{
	int i;

	if (arg_list[1] == NULL)
	{
		print_env(envp);
		return (0);
	}

	for (i = 1; arg_list[i] != NULL; i++)
		arg_list[i - 1] = arg_list[i];
	arg_list[i - 1] = arg_list[i];
	return (1);
}
/**
 * hsh_env_help - builtin help printout for env
 * Return: Always 0
 */
int hsh_env_help(void)
{
	_write("env usage: env\n    Prints out the current envirornment.\n");
	return (0);
}
