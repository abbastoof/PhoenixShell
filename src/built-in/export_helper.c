/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:33:05 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/14 15:39:31 by mtoof            ###   ########.fr       */
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
			ft_putstr("Malloc\n");
			return (-1);
		}
		ft_putstr("declare -x ");
		ft_putstr(split[0]);
		if (split[1] != NULL)
		{
			ft_putstr("=\"");
			ft_putstr(split[1]);
			ft_putstr("\"");
		}
		else
			ft_putstr("=\"\"");
	}
	else
	{
		ft_putstr("declare -x ");
		ft_putstr(env->env_var[index]);
	}
	return (0);
}
