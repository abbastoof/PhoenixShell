/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:03:52 by atoof             #+#    #+#             */
/*   Updated: 2023/06/20 11:28:20 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close(t_cmd *node)
{
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
}

void	proc_signal_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr("\n");
}

int	open_files(t_cmd *pipex, char *infile_path, char *outfile_path)
{
	int	value;

	value = TRUE;
	pipex->infile = open(infile_path, O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("pipex");
		value = FALSE;
	}
	pipex->outfile = open(outfile_path, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
		error("pipex");
	return (value);
}

int	run_cmd(t_lst *lst, char **envv)
{
	t_lst	*node;

	node = lst;
	signal(SIGINT, proc_signal_handler);
	while (node)
	{
		node->cmd_info->pid = fork();
		if (node->cmd_info->pid == -1)
			error("run_cmd: fork");
		if (node->cmd_info->pid == 0)
			ft_child(node, envv);
		ft_close(node);
		if (node->cmd_info->pid > 0)
			node = node->next;
	}
	ft_wait(lst);
	signal(SIGINT, proc_signal_handler);
	return (0);
}
