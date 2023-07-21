
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

static int	write_lines_to_file(const char *filename, t_tree *tree)
{
	char	*input_line;
	int		fd;

	fd = open(filename, O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	while (1)
	{
		input_line = readline("> ");
		if (input_line != NULL && \
			ft_strcmp(tree->redir->file_name, input_line) != 0)
		{
			write(fd, input_line, ft_strlen(input_line));
			write(fd, "\n", 1);
			free(input_line);
		}
		else
			break ;
	}
	return (fd);
}

void	run_heredoc(t_tree *tree, t_env **env)
{
	char	*filename;
	int		fd;
	(void)env;
	// init_heredoc_sigs();
	filename = "/tmp/heredoc_temp_file";
	fd = write_lines_to_file(filename, tree);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (tree->type == TOKEN_CMD && tree->redir->next == NULL)
		dup2(fd, STDIN_FILENO);
	close(fd);
	echoing_control_chars(1);
	unlink(filename);
}
