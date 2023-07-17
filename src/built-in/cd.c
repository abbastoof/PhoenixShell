/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:43:48 by atoof             #+#    #+#             */
/*   Updated: 2023/07/17 17:51:17 by mtoof            ###   ########.fr       */
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

void	ft_cd(t_env *env, char **args)
{
	char	cwd[1024];
	char	*path;

	path = NULL;
	(void)env;
	if (error_handling(args) == -1)
		return ;
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = find_path(env->env_var, "OLDPWD=");
		if (path == NULL)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	if (path == NULL)
		path = args[1];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	if (path && chdir(path) < 0)
		perror("minishell: cd");
	path = NULL;
}
