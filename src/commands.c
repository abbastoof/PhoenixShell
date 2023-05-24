/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:56:57 by atoof             #+#    #+#             */
/*   Updated: 2023/05/24 17:02:56 by atoof            ###   ########.fr       */
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
		if (ft_strcmp(tokens[0], "export") == 0)
		{
			ptr = ft_realloc(env->env_var, env->counter + 2);
			free(env->env_var);
			env->env_var = ptr;
		}
		if (ft_strcmp(tokens[0], "env") == 0)
		{
			while (env->env_var[++i])
				printf("%s\n", env->env_var[i]);
		}
		if (ft_strcmp(tokens[0], "echo") == 0)
		{
			echo(tokens + 1);
		}
		free(tokens);
	}
}
