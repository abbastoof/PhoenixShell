/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/17 14:10:30 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(char *str)
{
	ft_putstr("bash: unset: `");
	ft_putstr(str);
	ft_putstr("': not a valid identifier\n");
}

static void	shrink_env(t_env *env, char *str)
{
	char	**new_var;
	int		index;

	index = 0;
	new_var = ft_calloc(sizeof(char *), env->counter);
	if (!new_var)
	{
		ft_putstr("Malloc error\n");
		return ;
	}
	while (env->env_var[index] != NULL)
	{
		if (ft_strncmp(env->env_var[index], str, ft_strlen(str)) == 0)
			index++;
		if (env->env_var[index] != NULL)
		{
			new_var[index] = ft_strdup(env->env_var[index]);
			index++;
		}
	}
	if (env->env_var != NULL)
		free_double_ptr(env->env_var);
	env->counter--;
	env->env_var = new_var;
}

static void	find_var_inside_env(char *str, t_env *env)
{
	int		index;

	index = 0;
	if (!str || !env->env_var)
		return ;
	while (env->env_var[index] != NULL)
	{
		if (ft_strncmp(str, env->env_var[index], ft_strlen(str)) == 0)
		{
			shrink_env(env, str);
			break ;
		}
		index++;
	}
}

void	ft_unset(char **args, t_env *env)
{
	int	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (ft_strchr(args[index], '='))
			handle_error(args[index]);
		else
			find_var_inside_env(args[index], env);
		index++;
	}
}
