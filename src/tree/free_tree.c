/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:45:22 by atoof             #+#    #+#             */
/*   Updated: 2023/07/03 12:46:48 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	free(redir->file_name);
	free_redir(redir->next);
	free(redir);
}

void	free_tree(t_tree *tree)
{
	char	**curr;

	curr = NULL;
	if (tree == NULL)
		return ;
	free(tree->cmd);
	if (tree->args != NULL)
	{
		curr = tree->args;
		while (*curr != NULL)
		{
			free(*curr);
			curr++;
		}
		free(tree->args);
	}
	free_redir(tree->redir);
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

void	clean_tree(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	free_tree(*tree);
	*tree = NULL;
}