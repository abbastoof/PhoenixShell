/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 14:19:39 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_chk(void)
{
	if (WIFEXITED(g_exit_status))
		return ;
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == 2)
		{
			ft_putchar('\n');
			g_exit_status += 128;
		}
		else if (WTERMSIG(g_exit_status) == 3)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_exit_status += 128;
		}
	}
}
