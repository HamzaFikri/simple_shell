#include "shell.h"

/**
 * is_builtin - This program checks to see if a command is
 * a builtin function and if so, executes it
 * @cmd: a vector array of command line arguments
 * @b: line_buffer created in main
 *
 * Return: 1 if command is a builtin, 0 otherwise
 */

int is_builtin(char **cmd, char *b)
{
	struct builtins builtins = { "env", "exit" };

	if (_strcmp(*cmd, builtins.env) == 0)
	{
		env_builtin();
		return (1);
	}
	else if (_strcmp(*cmd, builtins.exit) == 0)
	{
		exiter(cmd, b);
		return (1);
	}
	else
	{
		return (0);
	}
}


/**
 * exiter - This program frees the buffer and
 * exits the program
 * @cmd: a vector array of command line arguments
 * @b: line_buffer created in main
 *
 * Return: void
 */

void exiter(char **cmd, char *b)
{
	free(b);
	free_cmds(cmd);
	exit(0);
}


/**
 * env_builtin - This program is prints the current
 * environment
 *
 * Return: 0
 */
void env_builtin(void)
{
	int i = 0;
	char **env = environ;

	while (env[i])
	{
		write(STDOUT_FILENO, (const void *) env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
