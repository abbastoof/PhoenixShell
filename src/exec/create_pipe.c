/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/07/06 17:52:01 by atoof            ###   ########.fr       */
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

void	create_pipe(t_tree *tree)
{
	int	end[2];

	if (pipe(end) < 0)
		exit(1);
	if (child_proc_defsig() == 0)
	{
		if (dup2(end[FD_WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		close(end[FD_READ_END]);
		exec_tree(tree->left);
		exit(g_exit_code);
	}
	wait(&(g_data.exit_code));
	if (child_proc_defsig() == 0)
	{
		if (dup2(end[FD_READ_END], STDIN_FILENO) < 0)
			exit(1);
		close(end[FD_WRITE_END]);
		exec_tree(tree->right);
		exit(g_tree.exit_code);
	}
	close(end[FD_READ_END]);
	close(end[FD_WRITE_END]);
	wait(&g_exit_status);
}
