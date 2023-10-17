#include "shell.h"

/**
 * _env_get - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_env_get(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = array_str_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _env_rem_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _env_rem_var(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starting_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = node_del_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _env_set_var - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _env_set_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_string_copy(buf, var);
	_string_concatenates(buf, "=");
	_string_concatenates(buf, value);
	node = info->env;
	while (node)
	{
		p = starting_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_addend(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
