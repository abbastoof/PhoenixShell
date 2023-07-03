/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_delete_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/03 14:44:59 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_tree *tree)
{
	int	i;

	if (tree->cmd != NULL)
		printf("cmd = %s\n", tree->cmd);
	i = 0;
	if (tree->args != NULL)
	{
		while (tree->args[i])
		{
			printf("args = %s\n", tree->args[i]);
			i++;
		}
		if (tree->redir != NULL)
		{
			while (tree->redir)
			{
				printf("redir_type = %d\n", tree->redir->type);
				printf("file_name = %s\n", tree->redir->file_name);
				tree->redir = tree->redir->next;
			}
		}
	}
}

void	display_list(t_tree *tree)
{
	static int	indx;

	// if (!tree)
	// 	return ;
	if (tree->left != NULL && tree->left->type == TOKEN_PIPE)
	{
		if (indx == 0)
			indx = 1;
		indx++;
		display_list(tree->left);
		printf("pipe num(%d)\n", indx);
	}
	if ((tree->left != NULL && tree->left->type == TOKEN_CMD)
		&& (tree->right != NULL && tree->right->type == TOKEN_CMD))
	{
		printf("first pipe\n");
		printf("left->cmd = %s\n", tree->left->cmd);
		print_node(tree->left);
		printf("right->cmd = %s\n", tree->right->cmd);
		print_node(tree->right);
	}
	if (tree->left != NULL && tree->left->type == TOKEN_PIPE
		&& tree->right != NULL && tree->right->type == TOKEN_CMD)
		print_node(tree->right);
	else
		print_node(tree);
}

static void	free_redir_lst(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		if (redir->file_name != NULL)
		{
			free(redir->file_name);
			redir->file_name = NULL;
		}
		tmp = redir;
		redir = redir->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_node(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->cmd != NULL)
	{
		free(tree->cmd);
		tree->cmd = NULL;
	}
	if (tree->args != NULL)
	{
		free(tree->args);
		tree->args = NULL;
	}
	if (tree->redir != NULL)
		free_redir_lst(tree->redir);
}

void	free_tree(t_tree *tree)
{
	if (tree->left || tree->right)
	{
		if (tree->left != NULL)
			free_tree(tree->left);
		if (tree->right != NULL)
			free_tree(tree->right);
	}
	if (tree->cmd != NULL)
		printf("cmd = %s\n", tree->cmd);
	if (tree->type != TOKEN_PIPE)
		free_node(tree);
	if (tree != NULL)
	{
		free(tree);
	}
	tree = NULL;
}
