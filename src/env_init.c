/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:59:59 by atoof             #+#    #+#             */
/*   Updated: 2023/07/13 18:01:17 by mtoof            ###   ########.fr       */
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

static char	*findout_shlvl(t_env *env, int indx)
{
	int		res;
	char	**tmp;

	tmp = ft_split(env->env_var[indx], '=');
	if (!tmp)
	{
		ft_putstr("Malloc error\n");
		return (NULL);
	}
	res = ft_atoi(tmp[1]);
	res++;
	return (ft_ito(res));
}

static void	strdup_var(char *str, t_env *env, int index, char *res)
{
	env->env_var[index] = ft_strdup(str);
	if (env->env_var[index] == NULL)
	{
		ft_putstr("minishell: strdup\n");
		exit(EXIT_FAILURE);
	}
}

static void	skip_oldpwd_update_shlvl(t_env *env, char **envp)
{
	int		indx;
	char	*res;

	indx = 0;
	res = NULL;
	while (envp[indx])
	{
		if (ft_strncmp(envp[indx], "SHLVL=", 7) == 0)
		{
			res = findout_shlvl(env, indx);
			strdup_var("SHLVL=", env, indx, res);
			free(res);
			res = NULL;
			indx++;
		}
		if (ft_strncmp(envp[indx], "OLDPWD=", 7) == 0)
		{
			strdup_var("OLDPWD", env, indx, NULL);
			indx++;
		}
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
