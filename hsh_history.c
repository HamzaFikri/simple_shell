#include "shell.h"

/**
 * hsh_history - builtin command hsh_history, mimics builtin history
 * @arg_list: argrument list of input
 * @envp: environemental variable list
 * @mode: mode to direct which function to execute
 * Return: Always 0
 */
int hsh_history(char **arg_list, env_t *envp, int mode)
{
	static hist_t history = {NULL, NULL};

	if (mode == 0)
		create_history(&history, envp);
	else if (mode == 1)
		add_cmdhist(&history, arg_list[0]);
	else if (mode == 2)
		write_history(envp, &history);
	else
	{
		if (arg_list[1] != NULL)
		{
			_write("Error: no such command\n");
			return (2);
		}
		print_history_2(&history);
	}
	return (0);
}

/**
 * print_history_2 - prints out the history with index
 * @history: history linked list
 */

void print_history_2(hist_t *history)
{
	int i, count;
	char *num_str;
	hist_t *temp, *temp2;

	history = history->next;
	for (count = 0, temp = history; temp != NULL; temp = temp->next, count++)
		;
	history = history->next;
	for (i = 0, temp2 = history; temp2 != NULL; temp2 = temp2->next, i++)
	{
		num_str = _itoa(i, 2);
		_write(" ");
		_write(num_str);
		_write(" ");
		_write(temp2->cmd);
		_write("\n");
	}
}
/**
 * hsh_history_help - builtin help printout for history
 * Return: Always 0
 */
int hsh_history_help(void)
{
	_write("history usage: history\n    ");
	_write("Display the history list with line numbers.\n");
	return (0);
}

/**
 * _itoa - interger to string converter
 * @num: number to convert
 * @mode: mode to determine how to deal with 0
 * Return: a string for the number
 */

char *_itoa(int num, int mode)
{
	char *num_str;
	int index, exp, i, temp_exp;

	num_str = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(num_str, '\0', BUFSIZE);
	exp = 1000000000;
	index = 0;
	if (num != 0)
	{
		while ((num / exp) == 0)
			exp /= 10;
		temp_exp = exp;
		while (temp_exp < 1000 && mode == 2)
		{
			num_str[index++] = 0 + '0';
			temp_exp *= 10;
		}
		while (exp >= 1)
		{
			num_str[index++] = (num / exp) + '0';
			num %= exp;
			exp /= 10;
		}
	}
	else
	{
		if (mode == 2)
		{
			for (i = 0; i < 4; i++)
				num_str[i] = 0 + '0';
		}
		else
			num_str[0] = 0 + '0';
	}
	return (num_str);
}
