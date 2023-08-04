/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 15:04:29 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  The last line of exec_tree is needed because we
	want our exit code to always remain between 0 and 255*/

/*  X_OK for execute/search permission),
	the existence test (F_OK)*/

void	exec_tree(t_tree **tree, t_env **env)
{
	if (*tree != NULL)
	{
		init_signals(0);
		if ((*tree)->type == TOKEN_PIPE)
			create_pipe(&(*tree), env);
		else if ((*tree)->type >= TOKEN_INPUT && (*tree)->type <= TOKEN_HEREDOC)
			exec_cmd_redir((*tree)->redir, tree, env);
		else if ((*tree)->type == TOKEN_CMD)
		{
			exec_cmd(&(*tree), env);
		}
		g_tree.exit_status = g_tree.exit_status % 255;
	}
}
