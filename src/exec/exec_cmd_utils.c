/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/18 16:59:59 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_chk(int exit_sig)
{
	g_tree.exit_status = WEXITSTATUS(exit_sig);
	if (WIFSIGNALED(exit_sig))
	{
		if (WTERMSIG(exit_sig) == 2)
			ft_putchar('\n');
		else if (WTERMSIG(exit_sig) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (WTERMSIG(exit_sig) == SIGSEGV)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		else if (WTERMSIG(exit_sig) == SIGBUS)
			ft_putstr_fd("Bus error: 10\n", 2);
		g_tree.exit_status = 128 + WTERMSIG(exit_sig);
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

static void	child_handler(int sig)
{
	(void)sig;
	return ;
}

void	child_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = child_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	run_cmd_in_child(t_tree *tree, char **env)
{
	init_signals(0);
	signal(SIGQUIT, SIG_IGN);
	if (child_process() == 0)
	{
		child_signal();
		if (execve(tree->cmd, tree->args, env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}
