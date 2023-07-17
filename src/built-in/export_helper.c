/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:33:05 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/17 16:41:27 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_function(char **split, t_env *env, int index)
{
	if (ft_strchr(env->env_var[index], '='))
	{
		split = ft_split(env->env_var[index], '=');
		if (!split)
		{
			ft_putstr_fd("Malloc\n", 2);
			return (-1);
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(split[0], 1);
		if (split[1] != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(split[1], 1);
			ft_putstr_fd("\"", 1);
		}
		else
			ft_putstr_fd("=\"\"", 1);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->env_var[index], 1);
	}
	return (0);
}

int	free_env_assign_new_var(char **new_env, t_env *env, char *var)
{
	if (env->env_var != NULL)
		free_double_ptr(env->env_var);
	new_env[env->counter] = ft_strdup(var);
	if (!new_env[env->counter])
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (-1);
	}
	env->counter++;
	return (0);
}
