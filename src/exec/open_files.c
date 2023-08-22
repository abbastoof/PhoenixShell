/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:55:34 by atoof             #+#    #+#             */
/*   Updated: 2023/08/22 15:44:57 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_output_file(t_redir *redir, t_tree *tree)
{
	if (redir->type == TOKEN_OUTPUT)
	{
		tree->fd_out = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		if (tree->fd_out == -1)
			error_access_filename(redir->file_name);
	}
	else if (redir->type == TOKEN_OUTPUT_APPEND)
	{
		tree->fd_out = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if (tree->fd_out == -1)
			error_access_filename(redir->file_name);
	}
}

void	open_input_file(t_redir *redir, t_tree *tree)
{
	tree->fd_in = open(redir->file_name, O_RDONLY);
	if (tree->fd_in == -1)
		error_access_filename(redir->file_name);
	if (redir->last == 1)
		dup2(tree->fd_in, STDIN_FILENO);
	close(tree->fd_in);
}
