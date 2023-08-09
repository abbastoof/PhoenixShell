/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/09 18:37:36 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_redir *redir, t_tree *tree)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_HEREDOC)
			run_heredoc(tmp, tree);
		if (tmp->last == 0)
			unlink(tmp->file_name);
		tmp = tmp->next;
	}
}

int	check_for_heredoc(t_tree **tree)
{
	if (tree != NULL)
	{
		if ((*tree)->left != NULL && (*tree)->left->type == TOKEN_PIPE)
			check_for_heredoc(&(*tree)->left);
		if ((*tree)->left->type == TOKEN_CMD && (*tree)->left->redir != NULL)
		{
			if ((*tree)->left->redir != NULL)
				check_for_last((*tree)->left->redir);
			exec_heredoc((*tree)->left->redir, (*tree)->left);
		}
		if ((*tree)->right->type == TOKEN_CMD && (*tree)->right->redir != NULL)
		{
			if ((*tree)->right->redir != NULL)
				check_for_last((*tree)->right->redir);
			exec_heredoc((*tree)->right->redir, (*tree)->right);
		}
		if ((*tree)->type == TOKEN_CMD && (*tree)->redir != NULL)
		{
			if ((*tree)->redir != NULL)
				check_for_last((*tree)->redir);
			exec_heredoc((*tree)->redir, *tree);
		}
	}
	return (0);
}
