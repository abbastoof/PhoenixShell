/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:31:15 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 12:20:02 by mtoof            ###   ########.fr       */
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
	if (node->args_ptr != NULL)
	{
		if (add_args_list(node) == -1)
			return (-1);
		free_args_list(&node->args_ptr, node);
	}
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
	while (tmp)
	{
		if ((tmp)->type == TOKEN_PIPE)
		{
			if (parse_pipe(tree, &tmp) == -1)
				return (-1);
			tmp = tmp->next;
		}
		else
		{
			if (parse_cmd(tree, &tmp) == -1)
				return (-1);
		}
	}
	return (0);
}
