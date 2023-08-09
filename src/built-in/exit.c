/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/09 10:18:42 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digits(t_tree *tree, int indx, t_env **env)
{
	int	c;

	c = 0;
	while (tree->args[indx][c])
	{
		if (tree->args[indx][c] == '-' || tree->args[indx][c] == '+')
			c++;
		if (!ft_isdigit(tree->args[indx][c]) || (ft_strcmp(tree->args[1], "0")
				&& ft_atol(tree->args[1]) == 0))
		{
			ft_putstr_fd("exit\nMinishell: exit: ", 2);
			ft_putstr_fd(tree->args[indx], 2);
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
	ft_putstr_fd("exit\n", 2);
	exit_num = ft_atol(tree->args[1]);
	free_tree(&tree);
	free_env(env);
	exit(exit_num % 256);
}

static void	exit_without_args(t_tree *tree, t_env **env)
{
	int		pid;

	pid = 0;
	if (pid == getpid())
		ft_putstr_fd("exit\n", 2);
	free_tree(&tree);
	free_env(env);
	exit(0);
}

int	ft_exit(t_tree *tree, t_env **env)
{
	int		indx;

	indx = 1;
	if (tree->args[indx] != NULL)
	{
		check_digits(tree, indx, env);
		indx++;
		if (tree->args[indx] != NULL)
		{
			ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
			g_tree.exit_status = 1;
			return (1);
		}
		exit_with_a_number(tree, env);
	}
	else
		exit_without_args(tree, env);
	return (0);
}
