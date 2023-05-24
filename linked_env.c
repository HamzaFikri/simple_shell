#include "shell.h"

/**
 * create_envlist - creates a linked list with all environment
 * variables in the extern environ variable
 * Return: head of created list
 */

env_t *create_envlist(void)
{
	env_t *head;
	int i;

	head = NULL;
	for (i = 0; environ[i] != NULL; i++)
		add_env(&head, environ[i]);
	return (head);
}

/**
 * add_env - adds another environmental variable to the end
 * of the environemental variable linked list
 * @head: head of the linked list
 * @str: environmental variable value to store
 * Return: the address of the new element, on fail, program exits
 */

env_t *add_env(env_t **head, char *str)
{
	env_t *new_node;
	env_t *temp;

	new_node = safe_malloc(sizeof(env_t));
	new_node->value = _strdup(str);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

/**
 * remove_env - removes an environmental variable
 * @head: pointer to the head of the linked list
 * @index: the nth node to delete
 */

void remove_env(env_t **head, int index)
{
	env_t *temp;
	env_t *dnode;
	int i;
	/*DEBUG: Shouldn't this just remove env by name, why by index?*/
	i = 0;
	temp = *head;
	if (index == 0)
	{
		*head = (*head)->next;
		_free(temp->value);
		_free(temp);
	}
	else
	{
		while (i < index - 1)
		{
			temp = temp->next;
			i++;
		}
		dnode = temp->next;
		temp->next = dnode->next;
		_free(dnode);
	}
}


/**
 * print_env - prints all environmental variables and its values
 * @head: head pointer to the linked list
 */

void print_env(env_t *head)
{
	env_t *temp;

	temp = head;
	while (temp != NULL)
	{
		_write(temp->value);
		_write("\n");
		temp = temp->next;
	}
}

/**
 * update_env - updates an environemental variable
 * @envp: linked list of environemental variables
 * @name: the name of variable to update;
 * @value: the value to update env with
 * @buf_size: buffer size
 */

void update_env(env_t *envp, char *name, char *value, int buf_size)
{
	char *rep;
	env_t *temp;

	rep = safe_malloc(sizeof(char) * buf_size);
	_memset(rep, '\0', buf_size);
	_strcat(rep, name);
	_strcat(rep, value);
	for (temp = envp; temp != NULL; temp = temp->next)
	{
		if (_strstr(temp->value, name) != NULL && temp->value[0] == name[0])
		{
			temp->value = rep;
			break;
		}
	}
}
