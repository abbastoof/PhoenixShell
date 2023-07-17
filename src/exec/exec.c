/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/17 13:20:00 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  The last line of exec_tree is needed because we
	want our exit code to always remain between 0 and 255*/

/*  X_OK for execute/search permission),
	the existence test (F_OK)*/

void	exec_tree(t_tree *tree, t_env *env)
{
	if (tree != NULL)
	{
		if (tree->type == TOKEN_PIPE)
			create_pipe(tree, env);
		//TODO:FIX THIS PART

		else if (tree->type >= TOKEN_INPUT && tree->type <= TOKEN_OUTPUT_APPEND)
			exec_redir_2(tree->redir, tree);
		else if (tree->type == TOKEN_CMD)
		{
			if (built_in(tree, env) == 0)
				exec_cmd(tree, env);
		}
		else if (tree->type == TOKEN_HEREDOC)
			exec_heredoc(tree);
		g_exit_status = g_exit_status % 255;
	}
}
