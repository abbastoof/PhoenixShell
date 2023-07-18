/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/07/18 18:04:27 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_handling(char **args)
{
	int	index;

	index = 0;
	if (!args || !args[1])
		return (-1);
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

static int	empty_oldpwd(void)
{
	ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
	return (-1);
}

static int	check_args(t_env *env, char **args, char *path, char *pwd_path)
{
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = find_path(env->env_var, "OLDPWD=");
		if (path == NULL)
			return (empty_oldpwd());
	}
	if (getcwd(pwd_path, 256) == NULL)
	{
		ft_putstr_fd("Minishell: getcwd\n", 2);
		return (-1);
	}
	return (0);
}

static void	change_path_update_env(char *path, t_env *env, char *pwd_path)
{
	char	*join;

	if (chdir(path) < 0)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	// join = ft_strjoin("PWD=", path);
	// find_var_in_env(path, env, "PWD=");
}

void	ft_cd(t_env *env, char **args)
{
	char	*path;
	char	*pwd_path;

	(void)env;
	path = NULL;
	pwd_path = NULL;
	pwd_path = ft_calloc(sizeof(char), 256);
	if (!pwd_path)
	{
		ft_putstr_fd("Malloc\n", 2);
		return ;
	}
	if (error_handling(args) == -1)
		return ;
	if (check_args(env, args, path, pwd_path) == -1)
		return ;
	if (path == NULL)
		path = args[1];
	change_path_update_env(path, env, pwd_path);
	path = NULL;
}
