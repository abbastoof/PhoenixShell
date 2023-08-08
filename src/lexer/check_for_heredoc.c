/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/08 14:08:07 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_heredoc(t_redir *redir, t_tree *tree)
{
	while (redir != NULL)
	{
		run_heredoc(redir, tree);
		//exit_check flag = 1 if (flag) ->do not run rest and exit from this file
		redir = redir->next;
	}
	if (redir->last == 1)
	{
		tree->fd_in = open("temp", O_RDONLY);
		dup2(tree->fd_in, STDIN_FILENO);
		close(tree->fd_in);
		unlink("temp");
	}
}

int	check_for_heredoc(t_tree **tree)
{
	t_redir	*tmp;

	tmp = NULL;
	if (tree != NULL)
	{
		if ((*tree)->left != NULL && (*tree)->left == TOKEN_PIPE)
			check_for_heredoc(&(*tree)->left);
		if ((*tree)->left == TOKEN_CMD && (*tree)->left->redir != NULL)
		{
			tmp = (*tree)->left->redir;
			exec_heredoc(tmp, (*tree)->left);
		}
		if ((*tree)->right == TOKEN_CMD && (*tree)->right->redir != NULL)
		{
			tmp = (*tree)->right->redir;
			exec_heredoc(tmp, (*tree)->right);
		}
		if ((*tree)->type == TOKEN_CMD && (*tree)->redir != NULL)
		{
			tmp = (*tree)->right->redir;
			exec_heredoc(tmp, tree);
		}
	}
	return (0);
}
