/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/05/24 16:23:53 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_environment *env, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			env->env_var = ft_realloc(env->env_var, env->counter + 2);
			env->env_var[env->counter++] = args[i];
		}
		else
			i++;
	}
}
