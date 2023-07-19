/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/19 12:53:48 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args, int args_indx)
{
	ft_putstr("Minishell: export: `");
	ft_putstr(args[args_indx]);
	ft_putstr("': not a valid identifier");
}

static void	print_export(t_env *env)
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

int	find_var_in_env(char *to_be_replaced, t_env *env, char *key)
{
	int	index;

	index = 0;
	while (env->env_var[index])
	{
		if (ft_strncmp(env->env_var[index], key, ft_strlen(key)) == 0)
		{
			free(env->env_var[index]);
			env->env_var[index] = ft_strdup(to_be_replaced);
			if (env->env_var[index] == NULL)
			{
				ft_putstr_fd("Malloc\n", 2);
				return (-1);
			}
			return (1);
		}
		index++;
	}
	return (0);
}

static char	**add_to_env(char *var, t_env *env)
{
	char	**new_env;
	char	*split;

	new_env = NULL;
	split = *ft_split(var, '=');
	if (!split)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (NULL);
	}
	if (find_var_in_env(var, env, &split[0]) == 0)
	{
		new_env = ft_realloc(env->env_var, env->counter + 2);
		if (!new_env || free_env_assign_new_var(new_env, env, var) == -1)
			return (NULL);
		return (new_env);
	}
	else
		return (NULL);
	if (split != NULL)
		free_double_ptr(&split);
	return (env->env_var);
}

void	ft_export(t_env *env, char **args)
{
	int		args_indx;
	char	**tmp;

	args_indx = 1;
	if (args[args_indx] != NULL)
	{
		while (args[args_indx] != NULL)
		{
			if (ft_isdigit(args[args_indx][0]))
				print_error(args, args_indx);
			else
			{
				tmp = add_to_env(args[args_indx], env);
				if (!tmp)
					break ;
				else
					env->env_var = tmp;
			}
		}
		args_indx++;
	}
	else
		print_export(env);
}
