/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/24 16:36:49 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digits(t_tree *tree, int index, t_env **env)
{
	int	c;

	c = 0;
	while (tree->args[index][c])
	{
		if (tree->args[index][c] == '-' || tree->args[index][c] == '+')
			c++;
		if (!ft_isdigit(tree->args[index][c]) || (ft_strcmp(tree->args[1], "0")
			&& ft_atoll(tree->args[1]) == 0))
		{
			ft_putstr_fd("exit\nMinishell: exit: ", 2);
			ft_putstr_fd(tree->args[index], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_tree(&tree);
			free_env(env);
			exit(255);
		}
		c++;
	}
}

static void	exit_with_a_number(t_tree *tree, t_env **env)
{
	long	exit_num;

	exit_num = 0;
	ft_putstr_fd("exit\n", 1);
	exit_num = ft_atoll(tree->args[1]);
	free_tree(&tree);
	free_env(env);
	exit((unsigned char)exit_num);
}

static void	exit_without_args(t_tree *tree, t_env **env)
{
	free_tree(&tree);
	free_env(env);
	exit(g_exit_status);
}

static void	exit_null_args(t_tree *tree, t_env **env)
{
	ft_putstr_fd("exit\nMinishell: exit: ", 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_tree(&tree);
	free_env(env);
	exit(255);
}

int	ft_exit(t_tree *tree, t_env **env, pid_t parent_flag)
{
	int		index;

	index = 1;
	if (index < tree->size_args)
	{
		if (tree->args[index] == NULL)
			exit_null_args(tree, env);
		check_digits(tree, index, env);
		index++;
		if (tree->args[index] != NULL)
		{
			if (parent_flag == 1)
				ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			return (256);
		}
		exit_with_a_number(tree, env);
	}
	else
	{
		if (parent_flag == 1)
			ft_putstr_fd("exit\n", 1);
		exit_without_args(tree, env);
	}
	return (0);
}
