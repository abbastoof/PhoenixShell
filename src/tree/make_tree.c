/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:31:15 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 13:34:41 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_pipe(t_tree **tree, t_token **tokens)
{
	t_tree	*node;

	node = new_tree_node();
	if (!node)
		return (-1);
	node->type = (*tokens)->type;
	if ((*tree))
		node->left = *tree;
	*tree = node;
	(*tokens)++;
	return (0);
}

static int	parse_cmd(t_tree **tree, t_token **tokens)
{
	t_tree	*node;

	node = new_tree_node();
	if (!node)
		return (-1);
	node->type = TOKEN_CMD;
	if (parse_cmd_node(tokens, node) == -1)
		return (-1);
	if ((*tree && (*tree)->left && !(*tree)->right))
		(*tree)->right = node;
	else
		*tree = node;
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
		else
		{
			if (parse_cmd(tree, &tmp) == -1)
				return (-1);
		}
	}
	return (0);
}
