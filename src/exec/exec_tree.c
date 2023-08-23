/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 12:22:43 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_tree **tree, t_env **env, pid_t	parent_flag)
{
	if (*tree != NULL)
	{
		if ((*tree)->type == TOKEN_PIPE)
			create_pipe(&(*tree), env);
		else if ((*tree)->type >= TOKEN_INPUT && (*tree)->type <= TOKEN_HEREDOC)
			exec_cmd_redir((*tree)->redir, tree, env, parent_flag);
		else if ((*tree)->type == TOKEN_CMD)
			exec_cmd(&(*tree), env, parent_flag);
	}
}
