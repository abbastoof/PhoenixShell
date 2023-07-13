/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:12:50 by atoof             #+#    #+#             */
/*   Updated: 2023/07/13 14:55:11 by atoof            ###   ########.fr       */
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
	else if ((access(file_name, W_OK) != 0) || access(file_name, R_OK) != 0 \
			|| access(file_name, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 1;
		exit(1);
	}
}

static void	next_redirect(t_redir *redir)
{
	int	fd;

	fd = 0;
	while (redir != NULL)
	{
		if (redir->type == TOKEN_OUTPUT)
			fd = open(redir->file_name,
					O_CREAT | O_TRUNC | O_WRONLY,
					0644);
		else if (redir->type == TOKEN_OUTPUT_APPEND)
			fd = open(redir->file_name,
					O_CREAT | O_APPEND | O_WRONLY,
					0644);
		else if (redir->type == TOKEN_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1)
				error_access_filename(redir->file_name);
		}
		close(fd);
		redir = redir->next;
	}
}

static void	check_redir_type(int fd, t_redir *redir)
{
	if (redir->type == TOKEN_OUTPUT)
	{
		fd = open(redir->file_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (fd == -1)
			error_access_filename(redir->file_name);
		dup2(fd, STDOUT_FILENO);
	}
	else if (redir->type == TOKEN_INPUT)
	{
		fd = open(redir->file_name, O_RDONLY);
		if (fd == -1)
			error_access_filename(redir->file_name);
		dup2(fd, STDIN_FILENO);
	}
	else if (redir->type == TOKEN_OUTPUT_APPEND)
	{
		fd = open(redir->file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd == -1)
			error_access_filename(redir->file_name);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}

int	exec_redir(t_redir *redir, t_tree *tree, t_env *env)
{
	int	fd;

	fd = 0;
	if (child_process() == 0)
	{
		check_redir_type(fd, redir);
		if (redir->next != NULL)
			next_redirect(redir->next);
		run_cmd_token(tree, env);
		exit(0);
	}
	wait(&(g_exit_status));
	return (1);
}
