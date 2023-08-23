/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 18:34:09 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	empty_key(char	*key)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
	return (-1);
}

static int	check_args(t_env **env, t_tree *tree, char **path, char **pwd_path)
{
	if (tree->args[1] == NULL && tree->size_args == 1)
	{
		*path = find_path(env, "HOME");
		if (*path == NULL)
			return (empty_key("HOME"));
	}
	if (ft_strcmp(tree->args[1], "-") == 0)
	{
		*path = find_path(env, "OLDPWD");
		if ((*path) == NULL)
			return (empty_key("OLDPWD"));
	}
	*pwd_path = getcwd(NULL, 0);
	return (0);
}

static int	error_handling(char *path)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (1);
}

static int	change_path_update_env(char *path, t_env **env, char *old_path)
{
	char	*pwd;

	if (chdir(path) < 0)
		return (error_handling(path));
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("Minishell: getcwd\n", 2);
		return (1);
	}
	find_key_in_env(env, "PWD", pwd);
	if (pwd != NULL)
	{
		free(pwd);
		pwd = NULL;
	}
	find_key_in_env(env, "OLDPWD", old_path);
	free_path(old_path);
	return (0);
}

int	ft_cd(t_env **env, t_tree *tree)
{
	char	*path;
	char	*current_path;

	current_path = NULL;
	path = NULL;
	if (tree->args[1] == NULL && tree->size_args > 1)
		return (0);
	if (check_args(env, tree, &path, &current_path) == -1)
		return (256);
	if (path == NULL)
		path = tree->args[1];
	if (change_path_update_env(path, env, current_path))
	{
		path = NULL;
		if (current_path != NULL)
			free_path(current_path);
		return (256);
	}
	return (0);
}
