/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 14:53:14 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	initialize_pipe(t_cmd *pipex)
// {
// 	pipex->pid = 0;
// 	pipex->end[0] = 0;
// 	pipex->end[1] = 0;
// 	pipex->infile = 0;
// 	pipex->outfile = 0;
// 	pipex->cmd_paths = NULL;
// 	pipex->cmd_arguments = NULL;
// 	pipex->cmd = NULL;
// }

// void	ft_wait(t_tree *tree)
// {
// 	t_tree	*node;
// 	int		status;

// 	node = tree;
// 	while (node)
// 	{
// 		waitpid(node->, &status, WUNTRACED);
// 		if (WIFEXITED(status))
// 			WEXITSTATUS(status);
// 		node = node->next;
// 	}
// }

void	create_pipe(t_tree **tree, t_env **env)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fds) < 0)
		exit(1);
	pid_left = fork();
	if (pid_left < 0)
		exit(1);
	if (pid_left == 0)
	{
		close(pipe_fds[FD_READ_END]);
		if (dup2(pipe_fds[FD_WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_WRITE_END]);
		exec_tree(&(*tree)->left, env);
		exit(g_exit_status);
	}
	pid_right = fork();
	if (pid_right < 0)
		exit(1);
	if (pid_right == 0)
	{
		close(pipe_fds[FD_WRITE_END]);
		if (dup2(pipe_fds[FD_READ_END], STDIN_FILENO) < 0)
			exit(1);
		close(pipe_fds[FD_READ_END]);
		exec_tree(&(*tree)->right, env);
		exit(g_exit_status);
	}
	close(pipe_fds[FD_READ_END]);
	close(pipe_fds[FD_WRITE_END]);
	waitpid(pid_left, &g_exit_status, 0);
	waitpid(pid_right, &g_exit_status, 0);
}
