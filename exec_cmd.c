#include "shell.h"

/**
 * exec_cmd - This program creates a new child process,
 * executes a command, and waits for the child process
 * to update its status
 * @c: command
 * @cmd: vector array of pointers to commands
 *
 * Return: void
 */

void exec_cmd(char *c, char **cmd)
{
	pid_t newProcess;
	int status;
	char **envp = environ;

	newProcess = fork();
	if (newProcess < 0)
		perror(c);
	if (newProcess == 0)
	{
		execve(c, cmd, envp);
		perror(c);
		free(c);
		free_cmds(cmd);
		exit(98);
	}
	else
	{
		wait(&status);
	}
}
