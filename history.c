#include "shell.h"

/**
 * history_wrapper - determines what to do for history
 * @cmd: command for add history mode
 * @envp: environemental variable linked list
 * @mode: mode to determine what to do
 * Description: 'c' create mode to create list,
 * 'a' add history mode, and 'w' write to file mode
 */

void history_wrapper(char *cmd, env_t *envp, char mode)
{
	char **arg;

	arg = safe_malloc(sizeof(char *) * 2);
	if (mode == 'c')
		hsh_history(NULL, envp, 0);
	else if (mode == 'a')
	{
		arg[0] = safe_malloc(sizeof(char) * (_strlen(cmd) + 1));
		_memcpy(arg[0], cmd, _strlen(cmd) + 1);
		hsh_history(arg, envp, 1);
	}
	else if (mode == 'w')
		hsh_history(arg, envp, 2);
}
