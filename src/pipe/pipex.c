/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by atoof             #+#    #+#             */
/*   Updated: 2023/06/20 12:10:23 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	initialize_pipe(t_cmd *pipex)
{
	pipex->pid = 0;
	pipex->end[0] = 0;
	pipex->end[1] = 0;
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_arguments = NULL;
	pipex->cmd = NULL;
}

void	ft_wait(t_lst *lst)
{
	t_lst	*node;
	int		status;

	node = lst;
	while (node)
	{
		waitpid(node->cmd_info->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
		node = node->next;
	}
}

void	create_pipe(t_cmd *pipex)
{
	if (pipe(pipex->end) < 0)
		perror("pipex");
}
