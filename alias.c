#include "shell.h"

/**
 * alias_expansion - wrapper function for checking and replacing aliases
 * @b: buffer structure
 * @env_p: enviornment struct to pass along
 * Return: 1 on alias replacement, 0 if no replacement
 */
int alias_expansion(buffer *b, env_t *env_p)
{
	static int stop = 2;
	int i, size;
	char *argv, *argv_copy;

	size = 0, i = 0;
	while (b->buf[b->bp] == ' ' || b->buf[b->bp] == '\t')
		b->bp++;
	while (!_is_whitespace(b->buf[b->bp + size]))
		size++;

	argv = safe_malloc(sizeof(char) * (size + 1));
	argv_copy = argv;

	while (i < size)
		argv[i] = b->buf[b->bp + i], i++;
	argv[i] = '\0';

	hsh_alias(&argv, env_p, 0);

	if (argv != NULL)
	{
		buffer_word_erase(b, b->bp);
		buffer_insert(b, argv, b->bp);
		_free(argv_copy);
		if (stop++ == 10)
		{
			stop = 0;
			return (0);
		}
		return (1);
	}
	else
		_free(argv);
	stop = 0;
	return (0);
}
