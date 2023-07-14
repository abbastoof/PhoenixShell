/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/14 17:33:45 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_printing(char **args, int index, int flag)
{
	if (flag == 0)
	{
		if (ft_strcmp(args[1], "-n") == 0)
		{
			index++;
			flag = 1;
		}
	}
	if (args[index + 1] != (void *)0)
		ft_putstr(args[index]);
	else if ((args[index + 1] == (void *)0) && !(ft_strcmp(args[0], "-n")))
		ft_putstr(args[index]);
	else if ((args[index + 1] == (void *)0) \
	&& (ft_strcmp(args[0], "-n")) != 0)
		ft_putstr(args[index]);
}

void	ft_echo(char **args)
{
	int	index;
	int	flag;

	index = 1;
	flag = 0;
	while (args[index])
	{
		handle_printing(args, index, flag);
		index++;
	}
	if (args[index] == NULL)
		write(1, "\n", 2);
}
