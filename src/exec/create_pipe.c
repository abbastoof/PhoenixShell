/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/08 12:24:13 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_tree **tree, t_env **env)
{
	pid_t	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
		exit(1);
	if (child_process() == 0)
	{
		if (dup2(pipe_fds[FD_WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_READ_END]);
		close(pipe_fds[FD_WRITE_END]);
		exec_tree(&(*tree)->left, env);
		exit(g_tree.exit_status);
	}
	wait(&(g_tree.exit_status));
	if (child_process() == 0)
	{
		if (dup2(pipe_fds[FD_READ_END], STDIN_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_WRITE_END]);
		close(pipe_fds[FD_READ_END]);
		if (g_tree.exit_status == 1)
			exit(1);
		exec_tree(&(*tree)->right, env);
		exit(g_tree.exit_status);
	}
	close(pipe_fds[FD_READ_END]);
	close(pipe_fds[FD_WRITE_END]);
	wait(&(g_tree.exit_status));
}
