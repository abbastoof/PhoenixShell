/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/08 08:46:11 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digits(t_tree *tree, int indx)
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
			//free tokens
			//free env linked list and double ptr
			exit(255);
		}
		c++;
	}
}

int	ft_exit(t_tree *tree, t_env **env)
{
	int		indx;
	long	exit_num;
	int		pid;

	pid = 0;
	indx = 1;
	exit_num = 0;
	if (tree->args[indx] != NULL)
	{
		check_digits(tree, indx);
		indx++;
		if (tree->args[indx] != NULL)
		{
			ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
			g_tree.exit_status = 1;
			return (1);
		}
		ft_putstr_fd("exit\n", 2);
		exit_num = ft_atol(tree->args[1]);
		free_tree(&tree);
		free_env(env);
		//free tokens
		//free env linked list and double ptr
		exit(exit_num % 256);
	}
	else
	{
		if (pid == getpid())
			ft_putstr_fd("exit\n", 2);
		free_tree(&tree);
		//free tokens
		//free env linked list and double ptr
		exit(0);
	}
}
