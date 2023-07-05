/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:31:15 by atoof             #+#    #+#             */
/*   Updated: 2023/07/05 19:30:31 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_pipe(t_tree **tree, t_token **tokens)
{
	t_tree	*node;

	node = new_node();
	if (!node)
		return (-1);
	node->type = (*tokens)->type;
	if ((*tree))
		node->left = *tree;
	*tree = node;
	(*tokens)++;
	return (0);
}

static int	add_redir_node(t_tree **tree, t_token **tokens)
{
	t_redir	*tmp;

	tmp = NULL;
	tmp = redir_node(tokens, (*tokens)->type);
	if (!tmp)
		return (-1);
	if (add_back(&((*tree)->redir), tmp) == -1)
		return (-1);
	return (0);
}

static int	parse_redirect(t_tree **tree, t_token **tokens)
{
	t_tree	*node;

	if (*tree && redir((*tree)->type))
	{
		if (add_redir_node(tree, tokens) == -1)
			return (-1);
	}
	else
	{
		node = new_node();
		if (!node)
			return (-1);
		node->type = (*tokens)->type;
		node->redir = redir_node(tokens, (*tokens)->type);
		if (!node->redir)
			return (-1);
		if (*tree && (*tree)->left && (*tree)->type == TOKEN_PIPE
			&& !(*tree)->right)
			(*tree)->right = node;
		else
			(*tree) = node;
	}
	(*tokens)++;
	return (0);
}

static int	parse_cmd(t_tree **tree, t_token **tokens)
{
	t_tree	*node;

	if ((*tree && redir((*tree)->type)))
	{
		if (parse_cmd_node(tokens, (*tree)) == -1)
			return (-1);
	}
	else if (*tree && (*tree)->right && redir((*tree)->right->type))
	{
		if (parse_cmd_node(tokens, (*tree)->right) == -1)
			return (-1);
	}
	else
	{
		node = new_node();
		if (!node)
			return (-1);
		if (parse_cmd_node(tokens, node) == -1)
			return (-1);
		if ((*tree && (*tree)->left && !(*tree)->right))
			(*tree)->right = node;
		else
			*tree = node;
	}
	return (0);
}

int	create_tree(t_token **tokens, t_tree **tree)
{
	t_token	*tmp;

	tmp = *tokens;

	while ((tmp)->value != NULL)
	{
		if ((tmp)->type == TOKEN_PIPE)
		{
			if (parse_pipe(tree, &tmp) == -1)
				return (-1);
		}
		else if (redir((tmp)->type))
		{
			if (parse_redirect(tree, &tmp) == -1)
				return (-1);
		}
		else
		{
			if (parse_cmd(tree, &tmp) == -1)
				return (-1);
		}
	}
	return (0);
}
