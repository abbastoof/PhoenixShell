/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:12:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/01 19:16:53 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_output_file(t_redir *redir, int *fd)
{
	if (redir->type == TOKEN_OUTPUT)
	{
		*fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*fd == -1)
			error_access_filename(redir->file_name);
	}
	else if (redir->type == TOKEN_OUTPUT_APPEND)
	{
		*fd = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*fd == -1)
			error_access_filename(redir->file_name);
	}
}

static void	open_input_file(t_redir *redir, t_tree *tree)
{
	// int	fd;

	tree->fd_in = open(redir->file_name, O_RDONLY);
	if (tree->fd_in == -1)
		error_access_filename(redir->file_name);
	dup2(tree->fd_in, STDIN_FILENO);
	close(tree->fd_in);
}

static void	exec_redirect(t_redir *redir, t_tree *tree)
{
	t_redir	*tmp_redir;
	int		fd;

	fd = 0;
	tmp_redir = redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == TOKEN_INPUT)
			open_input_file(tmp_redir, tree);
		else if (tmp_redir->type == TOKEN_OUTPUT
			|| tmp_redir->type == TOKEN_OUTPUT_APPEND)
		{
			open_output_file(tmp_redir, &fd);
			if (tree->last_redir != NULL)
				close(tree->fd_out);
			tree->fd_out = fd;
			tree->last_redir = tmp_redir;
		}
		tmp_redir = tmp_redir->next;
	}
	if (tree->last_redir != NULL)
	{
		dup2(tree->fd_out, STDOUT_FILENO);
		close(tree->fd_out);
	}
}

int	exec_cmd_redir(t_redir *redir, t_tree **tree, t_env **env)
{
	t_redir	*tmp_redir;

	if (child_process() == 0)
	{
		tmp_redir = redir;
		while (tmp_redir != NULL)
		{
			if (tmp_redir->type == TOKEN_HEREDOC)
				run_heredoc(*tree);
			tmp_redir = tmp_redir->next;
		}
		exec_redirect(redir, (*tree));
		if ((*tree)->cmd != NULL)
			run_cmd_token((*tree), env);
		exit(0);
	}
	wait(&(g_exit_status));
	return (1);
}
