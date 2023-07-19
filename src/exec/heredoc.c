/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:19:45 by atoof             #+#    #+#             */
/*   Updated: 2023/07/19 13:11:02 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_heredoc(t_tree *tree, t_env *env)
{
	int		end[2];
	char	*line;

	if (pipe(end) < 0)
		exit(1);
	if (child_process() == 0)
	{
		close(end[0]);
		dup2(g_stdout, STDOUT_FILENO);
		dup2(g_stdin, STDIN_FILENO);
		line = readline("> ");
		while (line && ft_strncmp(tree->redir->file_name, line,
				ft_strlen(tree->redir->file_name)) != 0)
		{
			free(line);
			line = readline("> ");
		}
		if (line)
			free(line);
		close(end[1]);
	}
	else
	{
		wait(NULL);
		dup2(end[FD_WRITE_END], STDIN_FILENO);
		close(end[FD_READ_END]);
		exec_tree(tree->left, env);
	}
	wait(&(g_exit_status));
	g_exit_status = g_exit_status % 255;
}
