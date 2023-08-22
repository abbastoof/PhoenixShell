/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:12:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/22 15:43:20 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_last_heredoc(t_redir *tmp_redir, t_tree *tree)
{
	if (tmp_redir->last == 1)
	{
		tree->fd_in = open(tmp_redir->file_name, O_RDONLY);
		if (tree->fd_in < 0)
		{
			perror("open");
			return ;
		}
		dup2(tree->fd_in, STDIN_FILENO);
		close(tree->fd_in);
	}
}

static void	exec_redirect(t_redir *redir, t_tree *tree)
{
	t_redir	*tmp_redir;

	tmp_redir = redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == TOKEN_INPUT)
			open_input_file(tmp_redir, tree);
		else if (tmp_redir->type == TOKEN_OUTPUT \
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
		else if (tmp_redir->type == TOKEN_HEREDOC)
			dup_last_heredoc(tmp_redir, tree);
		tmp_redir = tmp_redir->next;
	}
}

int	exec_cmd_redir(t_redir *redir, t_tree **tree, t_env **env,
		pid_t parent_flag)
{
	int	exit_sig;

	if (child_process() == 0)
	{
		if (redir != NULL)
			check_for_last(redir);
		exec_redirect(redir, (*tree));
		if (g_exit_status == 1)
			return (1);
		if ((*tree)->cmd != NULL)
		{
			if (built_in(&(*tree), env, parent_flag) == 0)
				run_cmd_token((*tree), env);
		}
		exit(0);
	}
	wait(&(exit_sig));
	exit_status_chk(exit_sig);
	return (1);
}
