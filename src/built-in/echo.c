/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 19:45:27 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *option)
{
	int	index;

	index = 1;
	if (!option || !option[0] || option[0] != '-')
		return (-1);
	while (option[index] == 'n')
		index++;
	if (index != (int)ft_strlen(option))
		return (-1);
	return (0);
}

int	ft_echo(t_tree *tree)
{
	int	index;
	int	flag;

	index = 1;
	flag = 0;
	if (tree->args[1] != NULL && tree->args[1][0] == '-')
	{
		while (check_flag(tree->args[index]) == 0)
		{
			flag = 1;
			index++;
		}
	}
	while (index < tree->size_args)
	{
		if (tree->args[index] != NULL)
			ft_putstr_fd(tree->args[index], 1);
		if (index + 1 < tree->size_args)
			ft_putchar(' ');
		index++;
	}
	if (flag == 0)
		ft_putchar('\n');
	return (0);
}
