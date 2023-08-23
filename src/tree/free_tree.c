/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_delete_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 16:41:12 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir_lst(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (redir->file_name)
				unlink(redir->file_name);
		}
		if (redir->file_name != NULL)
		{
			free(redir->file_name);
			redir->file_name = NULL;
		}
		if (redir->key)
		{
			free(redir->key);
			redir->key = NULL;
		}
		tmp = redir;
		redir = redir->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_node(t_tree *tree)
{
	int	index;

	if (tree == NULL)
		return ;
	if (tree->cmd != NULL)
	{
		free(tree->cmd);
		tree->cmd = NULL;
	}
	if (tree->args)
	{
		index = 0;
		while (index < tree->size_args)
		{
			free(tree->args[index]);
			tree->args[index] = NULL;
			index++;
		}
		free(tree->args);
		tree->args = NULL;
	}
	if (tree->redir != NULL)
		free_redir_lst(tree->redir);
	if (tree->cmd_paths != NULL)
		free_double_ptr(tree->cmd_paths);
}

void	free_tree(t_tree **tree)
{
	if (!tree)
		return ;
	if ((*tree) != NULL && ((*tree)->left != NULL || (*tree)->right != NULL))
	{
		if ((*tree)->left != NULL)
			free_tree(&(*tree)->left);
		if ((*tree)->right != NULL)
			free_tree(&(*tree)->right);
	}
	if ((*tree) != NULL && (*tree)->type != TOKEN_PIPE)
		free_node((*tree));
	if ((*tree) != NULL)
		free((*tree));
	(*tree) = NULL;
}
