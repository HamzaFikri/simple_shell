#include "shell.h"

/**
 * main - This program operates as a simple shell
 * @argc: the number of command line arguments
 * @argv: pointer to an array of command line
 * arguments
 * @envp: environment variable
 *
 * Return: Always 0
 *
 */

int main(int argc, char *argv[], char *envp[])
{
	char *line_buffer = NULL, *pathcmd = NULL, *path = NULL;
	size_t buffer_size = 0;
	ssize_t chars_in_line = 0;
	char **cmd = NULL, **paths = NULL;
	(void) envp, (void) argv;

	if (argc < 1)
		return (-1);
	signal(SIGINT, sighandle);
	while (1)
	{
		free_cmds(cmd);
		free_cmds(paths);
		free(pathcmd);
		prompt_printer();
		chars_in_line = getline(&line_buffer, &buffer_size, stdin);
		if (chars_in_line < 0)
			break;
		info.ln_count++;
		if (line_buffer[chars_in_line - 1] == '\n')
			line_buffer[chars_in_line - 1]  = '\0';
		cmd = token_maker(line_buffer);
		if (cmd == NULL || *cmd == NULL || **cmd == '\0')
			continue;
		if (check_type(cmd, line_buffer))
			continue;
		path = _getpath();
		paths = token_maker(path);
		pathcmd = try_paths(paths, cmd[0]);
		if (pathcmd == NULL)
			perror(argv[0]);
		else
			exec_cmd(pathcmd, cmd);
	}
	if (chars_in_line < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line_buffer);
	return (0);
}


/**
 * prompt_printer - This program prints the prompt if the
 * shell is in interactive mode
 *
 * Return: void
 */
void prompt_printer(void)
{
	if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
		flags.interactive = 1;
	if (flags.interactive)
		write(STDERR_FILENO, "$ ", 2);
}

/**
 * sighandle - This program allows ctrl+C to be
 * printed by the shell
 * @n: signum
 *
 * Return: void
 */
void sighandle(int n __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}


/**
 * check_type - This program checks the command
 * types to see if it is a built-in or executable
 * with a pathname
 * @cmd: array of pointers to command line arguments
 * @b: line buffer returned by getline function
 *
 * Return: 1 if the command is executed, 0 otherwise
 */
int check_type(char **cmd, char *b)
{
	if (is_builtin(cmd, b))
	{
		return (1);
	}
	else if (**cmd == '/')
	{
		exec_cmd(cmd[0], cmd);
		return (1);
	}
	return (0);
}
