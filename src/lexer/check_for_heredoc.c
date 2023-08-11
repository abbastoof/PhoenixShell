/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/11 11:19:14 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_for_heredoc(t_tree **tree)
{
    t_tree **tmp;
    
    tmp = tree;
    if (*tmp != NULL)
    {
        // init_signals(0);
        if ((*tmp)->type == TOKEN_PIPE)
        {
			if ((*tmp)->left && (*tmp)->left->type == TOKEN_PIPE)
				check_for_heredoc(&(*tmp)->left);
            if ((*tmp)->left && (*tmp)->left->type == TOKEN_CMD && contains_heredoc((*tmp)->left->redir))
                handle_only_heredoc_logic((*tmp)->left->redir, (*tmp)->left);
            if (g_tree.exit_status == 1)
                return (1);
			if ((*tmp)->right && (*tmp)->right->type == TOKEN_CMD && contains_heredoc((*tmp)->right->redir))
                handle_only_heredoc_logic((*tmp)->right->redir, (*tmp)->right);
             if (g_tree.exit_status == 1)
                return (1);
		}
        if ((*tmp)->type == TOKEN_CMD && contains_heredoc((*tmp)->redir))
        {
            handle_only_heredoc_logic((*tmp)->redir, *tmp);
            if (g_tree.exit_status == 1)
            return (1);
        }
		g_tree.exit_status = g_tree.exit_status % 255;
	}
    return (0);
}