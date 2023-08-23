/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:59 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 18:29:28 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_chk(int exit_sig)
{
	g_exit_status = WEXITSTATUS(exit_sig);
	if (WIFSIGNALED(exit_sig))
	{
		if (WTERMSIG(exit_sig) == SIGINT)
		{
			ft_putchar('\n');
			g_exit_status = 128 + WTERMSIG(exit_sig);
		}
		if (WTERMSIG(exit_sig) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_exit_status = 128 + WTERMSIG(exit_sig);
		}
		else if (WTERMSIG(exit_sig) == SIGSEGV)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		else if (WTERMSIG(exit_sig) == SIGBUS)
			ft_putstr_fd("Bus error: 10\n", 2);
	}
}

void	replace_cmd_absolute_path(t_tree *tree)
{
	char	*tmp;

	tmp = NULL;
	if (!tree->cmd)
		return ;
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
	if (sig == 2)
		printf("\n");
	return ;
}

void	child_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	sigemptyset(&s_act.sa_mask);
	s_act.sa_handler = child_handler;
	s_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_act, NULL);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = child_handler;
	sigaction(SIGQUIT, &s_quit, NULL);
}

void	run_cmd_in_child(t_tree *tree, char **env)
{
	signal(SIGINT, SIG_IGN);
	if (child_process() == 0)
	{
		child_signal();
		if (execve(tree->cmd, tree->args, env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tree->cmd, 2);
			if (tree->cmd != NULL && ft_strchr(tree->cmd, '/') && \
			access(tree->cmd, F_OK) == 0)
			{
				ft_putstr_fd(": is a directory\n", 2);
				exit(126);
			}
			else if (tree->cmd != NULL && ft_strchr(tree->cmd, '/') && \
			access(tree->cmd, F_OK) != 0)
				ft_putstr_fd(": No such file or directory\n", 2);
			else
				ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}
