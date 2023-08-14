/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 17:52:17 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_for_heredocs(t_redir *redir, t_tree *tree)
{
	check_for_last(redir);
	if (contains_heredoc(redir))
	{
		if (handle_only_heredoc_logic(redir, tree) == 1)
			return (1);
	}
	return (0);
}

int	check_for_heredoc(t_tree **tree)
{
	t_tree	**tmp;

	tmp = tree;
	if (*tmp != NULL)
	{
		init_signals(0);
		if ((*tmp)->left && (*tmp)->left->type == TOKEN_PIPE)
			if (check_for_heredoc(&(*tmp)->left) == 1)
				return (1);
		if ((*tmp)->left && (*tmp)->left->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->left->redir, (*tmp)->left) == 1)
				return (1);
		if ((*tmp)->right && (*tmp)->right->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->right->redir, (*tmp)->right) == 1)
				return (1);
		if ((*tmp)->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->redir, (*tmp)) == 1)
				return (1);
		g_tree.exit_status = g_tree.exit_status % 255;
	}
	return (0);
}
