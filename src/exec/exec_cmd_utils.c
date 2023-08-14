/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 16:25:32 by atoof            ###   ########.fr       */
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

void	replace_cmd_absolute_path(t_tree *tree)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_cmd(tree->cmd_paths, tree->cmd);
	if (!tmp)
	{
		ft_putstr_fd("Malloc in replace_cmd_absolute_path\n", 2);
		return ;
	}
	if (tree->cmd && ft_strcmp(tree->cmd, tmp) != 0)
	{
		free(tree->cmd);
		tree->cmd = tmp;
	}
}

void	run_cmd_in_child(t_tree *tree, char **env)
{
	if (child_process() == 0)
	{
		if (execve(tree->cmd, tree->args, env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}
