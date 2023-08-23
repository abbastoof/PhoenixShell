/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:19:45 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 17:23:17 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_lines_to_file(t_redir *redir, t_tree *tree)
{
	char	*input_line;

	tree->fd_in = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tree->fd_in < 0)
	{
		perror("open");
		return ;
	}
	input_line = readline("> ");
	while (input_line && ft_strcmp(redir->key, input_line) != 0)
	{
		if (input_line)
		{
			ft_putstr_fd(input_line, tree->fd_in);
			ft_putstr_fd("\n", tree->fd_in);
		}
		if (!input_line)
			exit(0);
		free(input_line);
		input_line = readline("> ");
	}
	if (input_line)
		free(input_line);
	close(tree->fd_in);
}

void	run_heredoc(t_redir *redir, t_tree *tree)
{
	init_signals(0);
	signal(SIGQUIT, SIG_IGN);
	if (child_process() == 0)
	{
		heredoc_signals();
		write_lines_to_file(redir, tree);
		echoing_control_chars(1);
		exit(0);
	}
}
