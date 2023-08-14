/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/09 11:11:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char **args, int args_indx, int flag)
{
	if (flag == 0)
	{
		ft_putstr("Minishell: export: `");
		ft_putstr(args[args_indx]);
		ft_putstr("': not a valid identifier\n");
	}
	else
	{
		ft_putstr_fd("Malloc error in ft_export()\n", 2);
		return (-1);
	}
	return (1);
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
					return (print_error(NULL, 0, 1));
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

static int	add_to_env(char *var, t_env **env)
{
	char	**split;
	int		flag;

	if (var != NULL && ft_strlen(ft_strrchr(var, '=')) > 1)
	{
		split = ft_split(var, '=');
		if (!split)
			return (print_error(NULL, 0, 1));
		if (find_key_in_env(env, split[0], split[1]) == 0)
		{
			if (split != NULL)
				free_double_ptr(split);
			return (0);
		}
	}
	else if (var != NULL)
	{
		flag = find_key_in_env(env, var, NULL);
		if (flag == 1)
			return (add_back_env(env, new_env_node(var)));
		else
			return (flag);
	}
	return (0);
}

int	ft_export(t_env **env, char **args)
{
	int	args_indx;
	int	flag;

	flag = 0;
	args_indx = 1;
	if (args[args_indx] != NULL)
	{
		while (args[args_indx] != NULL)
		{
			if (ft_isdigit(args[args_indx][0]))
				flag = print_error(args, args_indx, 0);
			else
			{
				if (add_to_env(args[args_indx], env) != 0)
					return (1);
			}
			args_indx++;
		}
	}
	else
		print_export(env);
	return (flag);
}
