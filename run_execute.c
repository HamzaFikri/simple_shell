#include "shell.h"

/**
 * run_execute - an execution function for the command given
 * @arg_list: argument list of what is inputed by user
 * @env_p: the linked list containing environmental variables
 * @cmd_size: size that cmd should be allocated for
 * Description: Checks if the command given is given the path (i.e /bin/ls)
 * if not, then the function will find the path for the command and if it fails
 * to find the command, an Error: command not found will be printed.
 * Return: status if success or 127 if failure.
 */

int run_execute(char **arg_list, env_t *env_p, int cmd_size)
{
	char *cmd, *path;
	char **search_path;
	int status, n, m;

	search_path = NULL;
	n = 0;
	cmd = safe_malloc(sizeof(char) * cmd_size);
	path = safe_malloc(sizeof(char) * cmd_size);
	_strcpy(cmd, arg_list[0]);
	if (_strchr(cmd, '/') != NULL)
		status = execute_func(cmd, arg_list, env_p);
	else
	{
		m = get_path(path, env_p);
		if (m != 0)
		{
			_write("Error: Cannot find PATH variable\n");
			return (127);
		}
		search_path = tokenize_path(search_path, path, cmd_size);
		n = create_path(cmd, search_path);
		if (n == 0)
			status = execute_func(cmd, arg_list, env_p);
	}
	if (n == 0)
		return (status);
	else
		return (127);
}

/**
 * execute_func - function that runs the execve system call.
 * @cmd: full path to the command
 * @args: the arguement list (if any) given by the user.
 * @envp: environemental variable list
 * Return: 0 on success and 2 on failure
 */

int execute_func(char *cmd, char **args, env_t *envp)
{
	pid_t pid;
	int status, i;
	char **array;


	pid = fork();
	if (pid == 0)
	{
		array = list_to_array(envp);
		i = execve(cmd, args, array);
		if (i < 0)
		{
			_write("Error: command not found\n");
			return (2);
			_exit(1);
		}
	}
	else
	{

		pid = wait(&status);
		if (WIFEXITED(status))
			return (status);
	}
	return (2);
}
