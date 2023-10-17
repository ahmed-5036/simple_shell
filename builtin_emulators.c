#include "shell.h"

/**
 * _shell_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _shell_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _string_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			error_mes(info, "Illegal number: ");
			_str_putss_(info->argv[1]);
			_char_putss_('\n');
			return (1);
		}
		info->err_num = _string_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _shell_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _shell_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_putss_("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _env_var_gett(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _env_var_gett(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_str_compare(info->argv[1], "-") == 0)
	{
		if (!_env_var_gett(info, "OLDPWD="))
		{
			_putss_(s);
			_putcharr('\n');
			return (1);
		}
		_putss_(_env_var_gett(info, "OLDPWD=")), _putcharr('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _env_var_gett(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		error_mes(info, "can't cd to ");
		_str_putss_(info->argv[1]), _char_putss_('\n');
	}
	else
	{
		_env_set_var(info, "OLDPWD", _env_var_gett(info, "PWD="));
		_env_set_var(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shell_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_putss_("help call works. Function not yet implemented \n");
	if (0)
		_putss_(*arg_array); /* temp att_unused workaround */
	return (0);
}
