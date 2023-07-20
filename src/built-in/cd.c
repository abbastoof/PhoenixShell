/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 19:46:21 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_handling(char **args)
{
	int	index;

	index = 0;
	while (args[index] != NULL)
		index++;
	if (index > 2)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}

static int	empty_key(char	*key)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
	return (-1);
}

static int	check_args(t_env **env, char **args, char **path, char **pwd_path)
{
	if (!args[1])
	{
		*path = find_path(env, "HOME");
		if (*path == NULL)
			return (empty_key("HOME"));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		*path = find_path(env, "OLDPWD");
		if ((*path) == NULL)
			return (empty_key("OLDPWD"));
	}
	if (getcwd(*pwd_path, 1024) == NULL)
	{
		ft_putstr_fd("Minishell: getcwd\n", 2);
		return (-1);
	}
	return (0);
}

static void	change_path_update_env(char *path, t_env **env, char *old_path)
{
	char	*pwd;

	pwd = ft_calloc(sizeof(char), 1024);
	if (chdir(path) < 0)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (getcwd(pwd, 1024) == NULL)
	{
		ft_putstr_fd("Minishell: getcwd\n", 2);
		return ;
	}
	find_key_in_env(env, "PWD", pwd);
	free(pwd);
	pwd = NULL;
	find_key_in_env(env, "OLDPWD", old_path);
}

void	ft_cd(t_env **env, char **args)
{
	char	*path;
	char	*current_path;

	(void)env;
	path = NULL;
	current_path = NULL;
	current_path = ft_calloc(sizeof(char), 1024);
	if (!current_path)
	{
		ft_putstr_fd("Malloc\n", 2);
		return ;
	}
	if (error_handling(args) == -1)
		return ;
	if (check_args(env, args, &path, &current_path) == -1)
		return ;
	if (path == NULL)
		path = args[1];
	change_path_update_env(path, env, current_path);
	path = NULL;
	free(current_path);
	current_path = NULL;
}
