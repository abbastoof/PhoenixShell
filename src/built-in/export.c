/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/10 19:02:10 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env)
{
	int		indx;
	char	**split;

	indx = 0;
	if (env->env_var[indx] == '\0')
		return ;
	while (env->env_var[indx] != NULL)
	{
		split = ft_split(env->env_var[indx], '=');
		if (!split)
			return ;
		ft_putstr("declare -x ");
		ft_putstr(split[0]);
		ft_putstr("=");
		ft_putstr("\"");
		if (split[1] != NULL)
			ft_putstr(split[1]);
		ft_putstr("\"");
		ft_putstr("\n");
		free(split[0]);
		free(split[1]);
		free(split);
		split = NULL;
		indx++;
	}
}

void	ft_export(t_env *env, char **args)
{
	int		args_indx;
	int		env_indx;
	char	**arg_split;
	// char	**new_var;

	arg_split = NULL;
	env_indx = 0;
	args_indx = 1;
	if (args[args_indx] != NULL)
	{
		while (args[args_indx])
		{
			if (ft_isdigit(args[args_indx][0]))
			{
				ft_putstr("Minishell: export: `");
				ft_putstr(args[args_indx]);
				ft_putstr("': not a valid identifier");
			}
			// else if (ft_strchr(args[args_indx], '='))
			// {
			// 	arg_split = ft_split(args[args_indx], '=');
			// 	while ((env->env_var[env_indx]) && ft_strncmp(arg_split[0], env->env_var[env_indx], ft_strlen(arg_split[0])) != 0)
			// 		env_indx++;
			// 	new_var = ft_realloc(env->env_var, ++env->counter);
			// 	new_var[env->counter] = args[args_indx];
			// 	free_env(env);
			// 	env->env_var = new_var;
			// }
			if (args[args_indx] != NULL)
				args_indx++;
		}
	}
	else
		print_export(env);
}
