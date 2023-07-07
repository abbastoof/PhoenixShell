/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/07 19:00:45 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digits(char **args, int indx, int c)
{
	while (args[indx][c])
	{
		if (args[indx][c] == '-' || args[indx][c] == '+')
			c++;
		if (!ft_isdigit(args[indx][c]))
		{
			ft_putstr_fd("exit\nMinishell: exit: ", 2);
			ft_putstr_fd(args[indx], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		c++;
	}
}

void	ft_exit(char **args)
{
	int	indx;
	int	c;

	indx = 1;
	c = 0;
	if (args[indx] != NULL)
	{
		check_digits(args, indx, c);
		indx++;
		if (args[indx] != NULL)
		{
			ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return ;
		}
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(args[1]) % 256);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(0 % 256);
	}
}
