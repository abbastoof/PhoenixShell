/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/21 19:31:09 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_child(t_tree **tree, t_env **env, pid_t pipe_fds[2])
{
	if (child_process() == 0)
	{
		if (dup2(pipe_fds[FD_WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_READ_END]);
		close(pipe_fds[FD_WRITE_END]);
		exec_tree(&(*tree)->left, env, 0);
		exit(g_exit_status);
	}
}

void	create_pipe(t_tree **tree, t_env **env)
{
	pid_t	pipe_fds[2];
	int		exit_status;

	if (pipe(pipe_fds) < 0)
		exit(1);
	signal(SIGINT, SIG_IGN);
	first_child(tree, env, pipe_fds);
	signal(SIGINT, SIG_DFL);
	if (child_process() == 0)
	{
		if (dup2(pipe_fds[FD_READ_END], STDIN_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_WRITE_END]);
		close(pipe_fds[FD_READ_END]);
		if (g_exit_status == 1)
			exit(1);
		exec_tree(&(*tree)->right, env, 0);
		exit(g_exit_status);
	}
	close(pipe_fds[FD_READ_END]);
	close(pipe_fds[FD_WRITE_END]);
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	exit_status_chk(exit_status);
}
