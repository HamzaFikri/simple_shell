#include "shell.h"

/**
 * hsh_unsetenv - builtin command hsh_unsetenv, mimics builtin unsetenv
 * @arg_list: arguement list for unstenv, contains the variable name
 * @envp: the linked list of all environment variables
 * Return: 0 on success and 1 on failure
 * Description: This will delete the node that contains the variable given, if
 * node does not exist then function will succeed
 */
int hsh_unsetenv(char **arg_list, env_t *envp)
{
	int count, len;
	env_t *temp;
	char *name;

	if (arg_list[1] == NULL)
	{
		/*_write("unsetenv: Too few arguments.\n");*/
		return (2);
	}
	len = _strlen(arg_list[1]);
	name = safe_malloc(sizeof(char) * (len + 2));
	_memcpy(name, arg_list[1], len + 1);
	_strncat(name, "=", 1);
	/* go through loop to search for environemental variable*/
	for (temp = envp, count = 0; temp != NULL; temp = temp->next)
	{
		if (_strstr(temp->value, name) != NULL)
		{
			remove_env(&envp, count);
			return (0);
		}
		count++;
	}
	return (2);
}
/**
 * hsh_unsetenv_help - builtin help printout for unsetenv
 * Return: Always 0
 */
int hsh_unsetenv_help(void)
{
	_write("unsetenv usage: unsetenv VARIABLE:\n    ");
	_write("Remove an envirornment variable.\n");
	return (0);
}
