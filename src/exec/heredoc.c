
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:19:45 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 17:43:54 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_lines_to_file(t_redir *redir, t_tree *tree)
{
	char	*input_line;

	tree->fd_in = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tree->fd_in < 0)
	{
		perror("open");
		return ;
	}
	input_line = readline("> ");
	while (input_line && ft_strcmp(redir->key, input_line) != 0)
	{
		if (g_tree.exit_status == 1)
			return ;
		if (input_line)
		{
			ft_putstr_fd(input_line, tree->fd_in);
			ft_putstr_fd("\n", tree->fd_in);
		}
		free(input_line);
		input_line = readline("> ");
	}
	if (input_line)
		free(input_line);
	close(tree->fd_in);
}

void	run_heredoc(t_redir *redir, t_tree *tree)
{
	if (child_process() == 0)
	{
		init_signals(0);
		dup2(g_tree.standard_input, STDIN_FILENO);
		dup2(g_tree.standard_output, STDOUT_FILENO);
		heredoc_signals();
		write_lines_to_file(redir, tree);
		if (tree->fd_in < 0)
		{
			perror("open");
			return ;
		}
		echoing_control_chars(1);
		exit(0);
	}
	wait(&(g_tree.exit_status));
	g_tree.exit_status = g_tree.exit_status % 255;
}
