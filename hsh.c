0000#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		infoo_clear(info);
		if (is_interact(info))
			_putss_("$ ");
		_char_putss_(BUF_FLUSH);
		r =  input_gett(info);
		if (r != -1)
		{
			infoo_set(info, av);
			builtin_ret = biult_in_find(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (is_interact(info))
			_putcharr('\n');
		infoo_free(info, 0);
	}
	history_write(info);
	infoo_free(info, 1);
	if (!is_interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int biult_in_find(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shell_exit},
		{"env", _current_env},
		{"help", _shell_help},
		{"history", _listMyHistory},
		{"setenv", _env_var_sett},
		{"unsetenv", _env_var_remo},
		{"cd", _shell_cd},
		{"alias", MyAlias_builtin},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delimeter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_cmd_path(info, _env_var_gett(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		command_fork(info);
	}
	else
	{
		if ((is_interact(info) || _env_var_gett(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_exec(info, info->argv[0]))
			command_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_mes(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void command_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _env_get(info)) == -1)
		{
			infoo_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_mes(info, "Permission denied\n");
		}
	}
}
