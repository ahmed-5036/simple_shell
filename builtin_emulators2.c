#include "shell.h"

/**
 * _listMyHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _listMyHistory(info_t *info)
{
	linkedlist_print(info->history);
	return (0);
}

/**
 * _AliasUnset - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _AliasUnset(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _string_char_search(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = node_del_index(&(info->alias),
		node_indx(info->alias, start_of_node(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _aliasSet - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _aliasSet(info_t *info, char *str)
{
	char *p;

	p = _string_char_search(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_AliasUnset(info, str));

	_AliasUnset(info, str);
	return (node_addend(&(info->alias), str, 0) == NULL);
}

/**
 * _aliasPrint - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _aliasPrint(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _string_char_search(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putcharr(*a);
		_putcharr('\'');
		_putss_(p + 1);
		_putss_("'\n");
		return (0);
	}
	return (1);
}

/**
 * MyAlias_builtin - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int MyAlias_builtin(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_aliasPrint(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _string_char_search(info->argv[i], '=');
		if (p)
			_aliasSet(info, info->argv[i]);
		else
			_aliasPrint(start_of_node(info->alias, info->argv[i], '='));
	}

	return (0);
}
