
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

static void	write_lines_to_file(const char *filename, t_tree *tree)
{
	char	*input_line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	while (1)
	{
		input_line = readline("> ");
		if (input_line != NULL && ft_strcmp(tree->redir->file_name, input_line) != 0)
		{
			write(fd, input_line, ft_strlen(input_line));
			write(fd, "\n", 1);
			free(input_line);
		}
		else
			break ;
	}
	close(fd);
}

void	run_heredoc(t_tree *tree, t_env **env)
{
	char	*filename;
	int		fd;

	// init_heredoc_sigs();
	filename = "/tmp/heredoc_temp_file";
	write_lines_to_file(filename, tree);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (tree->type == TOKEN_CMD)
		dup2(fd, 0);
	close(fd);
	disable_enable_ctl(1);
	exec_tree(tree->left, env);
	unlink(filename);
}
