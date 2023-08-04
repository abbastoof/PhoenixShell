/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 15:03:58 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_chk(void)
{
	if (WIFEXITED(g_tree.exit_status))
		return ;
	else if (WIFSIGNALED(g_tree.exit_status))
	{
		if (WTERMSIG(g_tree.exit_status) == 2)
		{
			ft_putchar('\n');
			g_tree.exit_status += 128;
		}
		else if (WTERMSIG(g_tree.exit_status) == 3)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_tree.exit_status += 128;
		}
	}
}
