/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:33:50 by atoof             #+#    #+#             */
/*   Updated: 2023/08/22 11:33:31 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_last(t_redir *redir)
{
	t_redir	*last_input;
	t_redir	*last_outfile;

	last_input = NULL;
	last_outfile = NULL;
	while (redir != NULL)
	{
		if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_INPUT)
			last_input = redir;
		if (redir->type == TOKEN_OUTPUT || redir->type == TOKEN_OUTPUT_APPEND)
			last_outfile = redir;
		redir = redir->next;
	}
	if (last_input != NULL)
		last_input->last = 1;
	if (last_outfile != NULL)
		last_outfile->last = 1;
}

int	contains_heredoc(t_redir *redir_list)
{
	t_redir	*current;

	current = redir_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

int	handle_only_heredoc_logic(t_redir *redir_list, t_tree *cmd_node)
{
	int		exitstatus;
	t_redir	*current_redir;

	exitstatus = 0;
	current_redir = redir_list;
	while (current_redir != NULL)
	{
		if (current_redir->type == TOKEN_HEREDOC)
		{
			run_heredoc(current_redir, cmd_node);
			wait(&(exitstatus));
			exit_status_chk(exitstatus);
			if (g_exit_status == 1)
				return (1);
			if (current_redir->last == 0)
				unlink(current_redir->file_name);
		}
		current_redir = current_redir->next;
	}
	return (0);
}

static int	go_for_heredocs(t_redir *redir, t_tree *tree)
{
	check_for_last(redir);
	if (contains_heredoc(redir))
	{
		if (handle_only_heredoc_logic(redir, tree) == 1)
			return (1);
	}
	return (0);
}

int	check_for_heredoc(t_tree **tree)
{
	t_tree	**tmp;

	tmp = tree;
	if (*tmp != NULL)
	{
		if ((*tmp)->left && (*tmp)->left->type == TOKEN_PIPE)
			if (check_for_heredoc(&(*tmp)->left) == 1)
				return (1);
		if ((*tmp)->left && (*tmp)->left->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->left->redir, (*tmp)->left) == 1)
				return (1);
		if ((*tmp)->right && (*tmp)->right->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->right->redir, (*tmp)->right) == 1)
				return (1);
		if ((*tmp)->type == TOKEN_CMD)
			if (go_for_heredocs((*tmp)->redir, (*tmp)) == 1)
				return (1);
	}
	return (0);
}
