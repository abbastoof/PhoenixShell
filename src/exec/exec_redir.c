/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:12:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/02 15:55:21 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_input_output_redirect(t_redir *redir, t_tree *tree)
{
	t_redir	*tmp_redir;

	tmp_redir = redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == TOKEN_INPUT)
			open_input_file(tmp_redir, tree);
		else if (tmp_redir->type == TOKEN_OUTPUT
			|| tmp_redir->type == TOKEN_OUTPUT_APPEND)
		{
			open_output_file(tmp_redir, tree);
			if (tmp_redir->last == 0)
				close(tree->fd_out);
			if (tmp_redir->last == 1)
			{
				dup2(tree->fd_out, STDOUT_FILENO);
				close(tree->fd_out);
			}
		}
		tmp_redir = tmp_redir->next;
	}
}

static void	exec_heredoc_redirect(t_redir *redir, t_tree *tree)
{
	t_redir	*tmp_redir;

	tmp_redir = redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == TOKEN_HEREDOC)
		{
			run_heredoc(tmp_redir, tree);
			if (tmp_redir->last == 1)
			{
				tree->fd_in = open("temp", O_RDONLY);
				dup2(tree->fd_in, STDIN_FILENO);
				close(tree->fd_in);
				unlink("temp");
			}
		}
		tmp_redir = tmp_redir->next;
	}
}

static void	exec_redirect(t_redir *redir, t_tree *tree)
{
	exec_input_output_redirect(redir, tree);
	exec_heredoc_redirect(redir, tree);
}

int	exec_cmd_redir(t_redir *redir, t_tree **tree, t_env **env)
{
	if (child_process() == 0)
	{
		if (redir != NULL)
			check_for_last(redir);
		exec_redirect(redir, (*tree));
		if ((*tree)->cmd != NULL)
			run_cmd_token((*tree), env);
		exit(0);
	}
	wait(&(g_exit_status));
	return (1);
}
