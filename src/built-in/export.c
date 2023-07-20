/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 12:10:47 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args, int args_indx)
{
	ft_putstr("Minishell: export: `");
	ft_putstr(args[args_indx]);
	ft_putstr("': not a valid identifier");
}

static void	print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		if (tmp->value != NULL)
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("\"\"\n", 1);
		tmp = tmp->next;
	}
}

int	find_key_in_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value != NULL)
			{
				if (tmp->value != NULL)
					free(tmp->value);
				tmp->value = ft_strdup(value);
				if (!tmp->value)
					return (-1);
					//protect malloc
			}
			return (0);
		}
		if (ft_strchr(key, '=') && value == NULL && ft_strncmp(tmp->key, key, \
		ft_strlen(key) - 1) == 0)
			return (empty_key_with_equal(&tmp));
		tmp = tmp->next;
	}
	return (1);
}

static void	add_to_env(char *var, t_env **env)
{
	char	*new_node;
	char	**split;

	new_env = NULL;
	split = ft_split(var, '=');
	if (!split)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (NULL);
	}
	if (find_var_in_env(var, env, split[0]) == 0)
	{
		new_env = ft_realloc(env->env_var, env->counter + 2);
		if (!new_env || free_env_assign_new_var(new_env, env, var) == -1)
			return (NULL);
		return (new_env);
	}
	else
		return (NULL);
	if (split != NULL)
		free_double_ptr(split);
	return (env->env_var);
}

void	ft_export(t_env **env, char **args)
{
	int	args_indx;

	args_indx = 1;
	if (args[args_indx] != NULL)
	{
		while (args[args_indx] != NULL)
		{
			if (ft_isdigit(args[args_indx][0]))
				print_error(args, args_indx);
			else
				add_to_env(args[args_indx], env);
			args_indx++;
		}
	}
	else
		print_export(env);
}
