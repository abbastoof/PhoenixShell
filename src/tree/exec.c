/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:36 by atoof             #+#    #+#             */
/*   Updated: 2023/07/06 18:31:05 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The last line of exec_tree is needed because we want our exit code to always remain between 0 and 255.

static void	exec_redir(t_tree *tree)
{
	int	fd;

	fd = 0;
	if (child_proc_defsig() == 0)
	{
		if (tree->type == TOKEN_OUTPUT)
		{
			fd = open(tree->redir->file_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				error_handling(tree->redir->file_name);
			dup2(fd, STDOUT_FILENO);
		}
		else if (tree->type == TOKEN_INPUT)
		{
			fd = open(tree->redir->file_name, O_RDONLY);
			if (fd == -1)
				error_handling(tree->redir->file_name);
			dup2(fd, STDIN_FILENO);
		}
		else if (tree->type == TOKEN_OUTPUT_APPEND)
		{
			fd = open(tree->redir->file_name, O_CREAT | O_APPEND | O_WRONLY,
					0644);
			if (fd == -1)
				error_handling(tree->redir->file_name);
			dup2(fd, STDOUT_FILENO);
		}
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
		g_exit_status = g_exit_status % 255;
	}
}
