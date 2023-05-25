/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:56:57 by atoof             #+#    #+#             */
/*   Updated: 2023/05/25 12:21:33 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_environment *env, const char *cmd)
{
	char	**tokens;
	char	**ptr;
	char	*path;
	int		i;

	i = 0;
	tokens = ft_split(cmd, ' ');
	if (tokens != NULL && tokens[0] != NULL)
	{
		if (ft_strcmp(tokens[0], "cd") == 0)
		{
			path = tokens[1];
			ft_cd(env, path);
		}
		else if (ft_strcmp(tokens[0], "export") == 0)
		{
			ptr = ft_realloc(env->env_var, env->counter + 2);
			free(env->env_var);
			env->env_var = ptr;
		}
		else if (ft_strcmp(tokens[0], "env") == 0)
		{
			while (env->env_var[++i])
				printf("%s\n", env->env_var[i]);
		}
		else if (ft_strcmp(tokens[0], "echo") == 0)
			echo(tokens + 1);
		else if (ft_strcmp(tokens[0], "pwd") == 0)
			pwd();
		free(tokens);
	}
}
