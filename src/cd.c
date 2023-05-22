/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/05/22 17:38:42 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	old_pwd(char *path, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "OLDPWD", 6) != NULL)
		{
			path = env[i] + 7;
			printf("%s\n", path);
		}
		i++;
	}
	if (env[i] == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (-1);
	}
	return (0);
}

int	dollorsign_exist(char **env, char *path)
{
	if ((path + 1) == NULL)
	{
		ft_putstr_fd("bash: cd: $: No such file or directory\n", 2);
		printf("got here\n");
		return (-1);
	}
	else
	{
		path = path + 1;
		path = find_path(env, path, NULL, 0);
		path += 1;
	}
	return (0);
}

void	cd(t_environment *env, char *args)
{
	char	*path;
	char	cwd[1024];

	if (!args)
		return ;
	else
		path = args;
	if (path[0] == '$')
	{
		if (dollorsign_exist(env->env_var, path) == -1)
			return ;
	}
	else if (ft_strcmp((const char *)path, "-") == 0)
	{
		if (old_pwd(path, env->env_var) == -1)
			return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	if (chdir(path) < 0)
		perror("minishell: cd");
	else
	{
		if (find_path(env->env_var, "OLDPWD=", NULL, 0) == NULL)
		{
			ft_realloc(env->env_var, env->counter + 2);
			find_path(env->env_var, "OLDPWD=", cwd, 1);
		}
		else
		{
			find_path(env->env_var, "OLDPWD=", cwd, 1);
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("minishell: getcwd");
		else
			find_path(env->env_var, "PWD=", cwd, 1);
	}
}
