#include "shell.h"

/**
 * create_history - creates a linked list for user
 * command history, size is 4096
 * @history: history linked list to pass
 * @envp: environmental variable linked list
 * Return: a pointer to the history linked list
 */

void create_history(hist_t *history, env_t *envp)
{
	char *str, *buf;
	int i, j, n;

	/* create a buf of what is in the file */
	buf = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(buf, '\0', BUFSIZE);
	n = read_file(envp, &buf);
	if (n > 0)
	{
		str = safe_malloc(sizeof(char) * _strlen(buf));
		if (*buf == '\0')
		{
			add_history(history, "");
		}
		/* create linked list and fill in with what is in file*/
		for (i = 0, j = 0; buf[i] != '\0'; i++)
		{
			if (buf[i] == '\n')
			{
				str[j] = '\0';
				add_history(history, str);
				j = 0;
			}
			else
				str[j++] = buf[i];
		}
	}
}

/**
 * print_history - prints the history
 * @head: the head of the linked list
 */

void print_history(hist_t *head)
{
	char *str;

	while (head != NULL)
	{
		str = _strdup(head->cmd);
		_write(str);
		_write("\n");
		head = head->next;
	}
}


/**
 * add_history - creates another history node to the linked list
 * @head: head of the history linked list
 * @cmd: command to store in list
 * Description: this function will add node to the end of the list
 * Return: a pointer to the new node
 */

hist_t *add_history(hist_t *head, char *cmd)
{
	hist_t *new_node;
	hist_t *temp;

	new_node = safe_malloc(sizeof(hist_t));
	new_node->cmd = _strdup(cmd);
	new_node->next = NULL;
	if (head == NULL)
		head = new_node;
	else
	{
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

/**
 * read_file - reads the simple_shell_history file and put it in a buffer
 * @envp: environemental variable linked list to get the HOME directory
 * @buf: buffer to input what is read
 * Return: 1 if success and 0 if failed
 */

int read_file(env_t *envp, char **buf)
{
	static int b_size = BUFSIZE;
	int offset, n, fd;
	char *path, *new_buf;

	path = rm_vname(envp, "HOME", BUFSIZE);
	if (path == NULL)
	{
		_write("Error: Cannot find Home\n");
		_write("Cannot find history file\n");
		return (1);
	}
	_strcat(path, "/.simple_shell_history");
	fd = open(path, O_RDWR | 0600);
	if (fd > 0)
	{
		offset = 0;
		while ((n = read(fd, *buf + offset, b_size - offset)) > 0)
		{
			if (n < b_size - offset)
			{
				(*buf)[n + offset] = '\0';
			}
			b_size *= 2;
			new_buf = safe_malloc((b_size) * sizeof(char));
			offset += n;
			_memcpy(new_buf, *buf, b_size / 2);
			*buf = new_buf;
		}
		close(fd);
		return (1);
	}
	return (0);
}
/**
 * make_path - makes the path
 * @path: path to create
 * @filename: filename to open
 * @key: key to create
 * @envp: environemental linked list
 * Return: the path str
 */
char *make_path(char **path, char *filename, char *key, env_t *envp)
{
	char *value;

	if (_strstr(key, "/"))
	{
		*path = filename;
		return (filename);
	}

	value = get_env_value(envp, key);
	*path = safe_malloc(sizeof(char) * (_strlen(value) + _strlen(filename) + 2));
	_memcpy(*path, value, _strlen(value) + 1);
	strcat(*path, "/");
	strcat(*path, filename);
	return (*path);
}
