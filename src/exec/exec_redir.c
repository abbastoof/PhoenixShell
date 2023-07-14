/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:12:50 by atoof             #+#    #+#             */
/*   Updated: 2023/07/14 14:25:07 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_access_filename(char *file_name)
{
	if (access(file_name, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		exit(1);
	}
	else if ((access(file_name, W_OK) != 0) || access(file_name, R_OK) != 0
		|| access(file_name, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 1;
		exit(1);
	}
}

static void	next_redirect(t_redir *redir, t_tree *tree)
{
	t_redir	*last_redir;
	t_redir	*tmp_redir;
	int		fd;

	last_redir = NULL;
	tmp_redir = redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == TOKEN_OUTPUT)
		{
			fd = open(tmp_redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				error_access_filename(tmp_redir->file_name);
		}
		else if (tmp_redir->type == TOKEN_OUTPUT_APPEND)
		{
			fd = open(tmp_redir->file_name, O_CREAT | O_WRONLY | O_APPEND,
					0644);
			if (fd == -1)
				error_access_filename(tmp_redir->file_name);
		}
		else if (tmp_redir->type == TOKEN_INPUT)
		{
			fd = open(tmp_redir->file_name, O_RDONLY);
			if (fd == -1)
				error_access_filename(tmp_redir->file_name);
			dup2(fd, STDIN_FILENO);
			close(fd);
			tmp_redir = tmp_redir->next;
			continue ;
		}
		else
		{
			tmp_redir = tmp_redir->next;
			continue ;
		}
		if (last_redir != NULL)
			close(tree->fd_out);
		tree->fd_out = fd;
		last_redir = tmp_redir;
		tmp_redir = tmp_redir->next;
	}
	if (last_redir != NULL)
		dup2(tree->fd_out, STDOUT_FILENO);
}

int	exec_redir(t_redir *redir, t_tree *tree, t_env *env)
{
	if (child_process() == 0)
	{
		next_redirect(redir, tree);
		run_cmd_token(tree, env);
		exit(0);
	}
	wait(&(g_exit_status));
	return (1);
}
