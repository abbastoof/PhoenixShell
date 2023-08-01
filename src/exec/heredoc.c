
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

// void	run_heredoc(t_tree *tree)
// {
// 	int		end[2];
// 	char	*line;

// 	if (pipe(end) < 0)
// 		exit(1);
// 	line = readline("> ");
// 	while (line && ft_strcmp(tree->redir->file_name, line) != 0)
// 	{
// 		if (line)
// 		{
// 			write(end[FD_WRITE_END], line, ft_strlen(line));
// 			write(end[FD_WRITE_END], "\n", 1);
// 		}
// 		free(line);
// 		line = readline("> ");
// 	}
// 	if (line)
// 		free(line);
// 	dup2(end[FD_READ_END], STDIN_FILENO);
// 	close(end[FD_WRITE_END]);
// 	close(end[FD_READ_END]);
// 	g_exit_status = g_exit_status % 255;
// }

static int	write_lines_to_file(t_tree *tree)
{
	char	*input_line;

	int	p[2];

	pipe(p);

	tree->fd_in = open("heredoc_temp_file",O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tree->fd_in < 0)
	{
		perror("open");
		return (-1);
	}
	input_line = readline("> ");
	while (input_line && ft_strncmp(tree->redir->file_name, input_line, \
		ft_strlen(input_line) + 1) != 0)
	{
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
	return (tree->fd_in);
}

void	run_heredoc(t_tree *tree)
{
	// init_heredoc_sigs();
	tree->fd_in = write_lines_to_file(tree);
	if (tree->fd_in < 0)
	{
		perror("open");
		return ;
	}
	if (tree->type == TOKEN_CMD)
		dup2(tree->fd_in, STDIN_FILENO);
	close(tree->fd_in);
	echoing_control_chars(1);
}
