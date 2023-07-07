/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:59:59 by atoof             #+#    #+#             */
/*   Updated: 2023/07/07 16:40:17 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_lines_to_env_var(t_env *env, char **envp, int indx)
{
	env->env_var[indx] = ft_strdup(envp[indx]);
	if (env->env_var[indx] == NULL)
	{
		perror("minishell: strdup");
		exit(EXIT_FAILURE);
	}
}

static void	skip_oldpwd_update_shlvl(t_env *env, char **envp)
{
	int	indx;

	indx = 0;
	while (envp[indx])
	{
		if (ft_strnstr(envp[indx], "SHLVL=", 7) != NULL)
		{
			env->env_var[indx] = ft_strdup("SHLVL=2");
			if (env->env_var[indx] == NULL)
			{
				perror("minishell: strdup");
				exit(EXIT_FAILURE);
			}
			indx++;
		}
		if (ft_strnstr(envp[indx], "OLDPWD=", 7) != NULL)
			indx++;
		if (envp[indx] != NULL)
			add_lines_to_env_var(env, envp, indx);
		indx++;
	}
}

void	initialize_environment(t_env *env, char **envp)
{
	env->counter = 0;
	while (envp[env->counter])
		env->counter++;
	env->env_var = ft_calloc(sizeof(char *), (env->counter + 1));
	if (env->env_var == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	skip_oldpwd_update_shlvl(env, envp);
}
