/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/12 13:56:19 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args, int args_indx)
{
	ft_putstr("Minishell: export: `");
	ft_putstr(args[args_indx]);
	ft_putstr("': not a valid identifier");
}

void	print_export(t_env *env)
{
	int		indx;
	char	**split;

	indx = 0;
	if (env->env_var[indx] == '\0')
		return ;
	while (env->env_var[indx] != NULL)
	{
		split = NULL;
		split = ft_split(env->env_var[indx], '=');
		if (!split)
			return ;
		ft_putstr("declare -x ");
		ft_putstr(split[0]);
		if (split[1] != NULL)
		{
			ft_putstr("=");
			ft_putstr("\"");
			ft_putstr(split[1]);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		free_double_ptr(split);
		indx++;
	}
}

static char	**add_to_env(char *new_var, t_env *env)
{
	char	**new_env;
	int		indx;

	indx = 0;
	new_env = NULL;
	new_env = ft_realloc(env->env_var, env->counter + 2);
	if (env->env_var != NULL)
		free_double_ptr(env->env_var);
	new_env[env->counter++] = ft_strdup(new_var);
	indx = 0;
	return (new_env);
}

void	ft_export(t_env *env, char **args)
{
	int		args_indx;
	char	**arg_split;

	arg_split = NULL;
	args_indx = 1;
	if (args[args_indx] != NULL)
	{
		while (args[args_indx] != NULL)
		{
			if (ft_isdigit(args[args_indx][0]))
				print_error(args, args_indx);
			else
			{
				env->env_var = add_to_env(args[args_indx], env);
			}
			args_indx++;
		}
	}
	else
		print_export(env);
}
