/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:19:45 by atoof             #+#    #+#             */
/*   Updated: 2023/07/17 14:16:23 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_tree *tree)
{
	int		fd;
	char	*line;

	fd = open(tree->tmp_file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strncmp(line, tree->redir->file_name,
				ft_strlen(tree->redir->file_name)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		add_history(line);
		free(line);
		line = readline("> ");
	}
	close(fd);
}
