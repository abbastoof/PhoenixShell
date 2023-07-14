/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/14 15:06:58 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(char *str)
{
	ft_putstr("bash: unset: `");
	ft_putstr(str);
	ft_putstr("': not a valid identifier\n");
}

static char	**shrink_env(t_env *env, char *str)
{
	char	**new_var;
	int		index;

	index = 0;
	new_var = ft_calloc(sizeof(char *), env->counter);
	if (!new_var)
	{
		ft_putstr("Malloc error\n");
		return (NULL);
	}
	while (env->env_var[index] != NULL)
	{
		if (str != NULL && ft_strncmp(env->env_var[index], str, ft_strlen(str)) == 0)
			index++;
		new_var[index] = ft_strdup(env->env_var[index]);
		index++;
	}
	free_double_ptr(env->env_var);
	return (new_var);
}

static char	**find_var_inside_env(char *str, t_env *env, int index)
{
	char	**tmp;

	tmp = NULL;
	if (ft_strncmp(env->env_var[index], str, ft_strlen(str)) == 0)
	{
		tmp = shrink_env(env, str);
		if (tmp == NULL)
			return (NULL);
	}
	return (tmp);
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
		{
			env->env_var = find_var_inside_env(args[index], env, index);
		}
		index++;
	}
}
