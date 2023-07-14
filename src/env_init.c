/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:59:59 by atoof             #+#    #+#             */
/*   Updated: 2023/07/14 15:07:16 by mtoof            ###   ########.fr       */
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

static char	*find_shlvl(char **env, int index)
{
	int		shlvl_value;
	char	**tmp;

	tmp = ft_split(env[index], '=');
	if (!tmp)
	{
		ft_putstr("Malloc error\n");
		return (NULL);
	}
	shlvl_value = ft_atoi(tmp[1]);
	shlvl_value += 1;
	return (ft_itoa(shlvl_value));
}

static void	strdup_var(char *str, t_env *env, int index, char *res)
{
	char	*tmp;

	tmp = NULL;
	if (str != NULL && ft_strncmp(str, "SHLVL=", 6) == 0)
	{
		tmp = ft_strjoin(str, res);
		env->env_var[index] = ft_strdup(tmp);
	}
	else
		env->env_var[index] = ft_strdup(str);
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	if (env->env_var[index] == NULL)
	{
		ft_putstr("minishell: strdup\n");
		exit(EXIT_FAILURE);
	}
}

static void	skip_oldpwd_update_shlvl(t_env *env, char **envp)
{
	int		indx;
	char	*shlvl_value;

	indx = 0;
	shlvl_value = NULL;
	while (envp[indx])
	{
		if (ft_strncmp(envp[indx], "SHLVL=", 6) == 0)
		{
			shlvl_value = find_shlvl(envp, indx);
			strdup_var("SHLVL=", env, indx, shlvl_value);
			free(shlvl_value);
			shlvl_value = NULL;
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
	while (envp[env->counter] != NULL)
		env->counter++;
	env->env_var = ft_calloc(sizeof(char *), env->counter + 1);
	printf("counter = %d\n", env->counter);
	if (env->env_var == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	skip_oldpwd_update_shlvl(env, envp);
}
