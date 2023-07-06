/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/06 17:16:04 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The last line of exec_tree is needed because we want our exit code to always remain between 0 and 255.

static void	exec_redir(t_tree *tree)
{
	if (tree)
	{
		if (tree->type == TOKEN_INPUT)
			
	}
}

void	exec_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->type == TOKEN_PIPE)
			create_pipe(tree);
		else if (redir(tree->type))
			exec_redir(tree);
		else if (tree->type == TOKEN_CMD)
			exec_cmd(tree);
		else if (tree->type == TOKEN_BLTIN)
			exec_builtin_leaf(tree);
		else if (tree->type == TOKEN_HEREDOC)
			exec_heredoc(tree);
		g_exit_status = g_exit_status % 255;
	}
}
