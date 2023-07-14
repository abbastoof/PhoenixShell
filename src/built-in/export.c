/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/14 10:29:52 by mtoof            ###   ########.fr       */
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
	int		index;
	char	**split;

	index = 0;
	if (env->env_var[index] != NULL)
	{
		while (env->env_var[index] != NULL)
		{
			split = NULL;
			if (print_function(split, env, index) == -1)
				return ;
			ft_putstr("\n");
			if (split != NULL)
				free_double_ptr(split);
			index++;
		}
	}
}

static int	find_var_in_env(char *var, t_env *env)
{
	int		index;
	char	**split;

	split = ft_split(var, '=');
	index = 0;
	while (env->env_var[index])
	{
		if (ft_strncmp(env->env_var[index], split[0], ft_strlen(split[0])) == 0)
		{
			free(env->env_var[index]);
			printf("var = %s\n", var);
			env->env_var[index] = ft_strdup(var);
			return (1);
		}
		index++;
	}
	free_double_ptr(split);
	return (0);
}

static char	**add_to_env(char *new_var, t_env *env)
{
	char	**new_env;
	int		indx;

	indx = 0;
	new_env = NULL;
	if (find_var_in_env(new_var, env) == 0)
	{
		new_env = ft_realloc(env->env_var, env->counter + 2);
		if (env->env_var != NULL)
			free_double_ptr(env->env_var);
		new_env[env->counter++] = ft_strdup(new_var);
		indx = 0;
		return (new_env);
	}
	return (env->env_var);
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
