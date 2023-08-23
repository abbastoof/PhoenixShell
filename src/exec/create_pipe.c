/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 14:53:44 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_child(t_tree **tree, t_env **env, pid_t pipe_fds[2], \
	pid_t *pid_left)
{
	*pid_left = child_process();
	if (*pid_left == 0)
	{
		if (dup2(pipe_fds[FD_WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_READ_END]);
		close(pipe_fds[FD_WRITE_END]);
		exec_tree(&(*tree)->left, env, 0);
		exit(g_exit_status);
	}
}

static void	close_fd_wait(pid_t *pipe_fds, pid_t pid_left, \
		pid_t pid_right)
{
	int	exit_status;

	close(pipe_fds[FD_READ_END]);
	close(pipe_fds[FD_WRITE_END]);
	waitpid(pid_left, &exit_status, 0);
	if (WTERMSIG(exit_status) == 13)
		ft_putchar('\n');
	waitpid(pid_right, &exit_status, 0);
	if (WTERMSIG(exit_status) == 13)
		ft_putchar('\n');
	exit_status_chk(exit_status);
}

void	create_pipe(t_tree **tree, t_env **env)
{
	pid_t	pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fds) < 0)
		exit(1);
	signal(SIGINT, SIG_IGN);
	first_child(tree, env, pipe_fds, &pid_left);
	pid_right = child_process();
	if (pid_right == 0)
	{
		if (dup2(pipe_fds[FD_READ_END], STDIN_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_WRITE_END]);
		close(pipe_fds[FD_READ_END]);
		exec_tree(&(*tree)->right, env, 0);
		exit(g_exit_status);
	}
	close_fd_wait(pipe_fds, pid_left, pid_right);
}
