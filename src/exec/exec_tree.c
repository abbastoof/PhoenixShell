/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/08/11 15:03:08 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_tree **tree, t_env **env)
{
	if (*tree != NULL)
	{
		// init_signals(1);
		if ((*tree)->type == TOKEN_PIPE)
			create_pipe(&(*tree), env);
		// else if ((*tree)->type >= TOKEN_INPUT && (*tree)->type <= TOKEN_HEREDOC)
		// 	exec_cmd_redir((*tree)->redir, tree, env);
		else if ((*tree)->type == TOKEN_CMD)
			exec_cmd(&(*tree), env);
		g_tree.exit_status = g_tree.exit_status % 255;
	}
}
