/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:31:15 by atoof             #+#    #+#             */
/*   Updated: 2023/07/03 09:25:06 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*parse_pipe(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	node = new_node();
	node->type = tokens->type;
	if ((*tree))
		node->left = *tree;
	*tree = node;
	tokens++;
	return (tokens);
}

static t_token	*parse_redirect(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	if (*tree && redir((*tree)->type))
		add_back(&(*tree)->redir, redir_node(&tokens, tokens->type));
	else
	{
		node = new_node();
		node->type = tokens->type;
		node->redir = redir_node(&tokens, tokens->type);
		if (*tree && (*tree)->left && (*tree)->type == TOKEN_PIPE
			&& !(*tree)->right)
			(*tree)->right = node;
		else
			(*tree) = node;
	}
	tokens++;
	return (tokens);
}

static t_token	*parse_cmd(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	if ((*tree && redir((*tree)->type)))
	{
		parse_cmd_node(&tokens, (*tree));
	}
	else if (*tree && (*tree)->right && redir((*tree)->right->type))
	{
		parse_cmd_node(&tokens, (*tree)->right);
	}
	else
	{
		node = new_node();
		parse_cmd_node(&tokens, node);
		if ((*tree && (*tree)->left && !(*tree)->right))
			(*tree)->right = node;
		else
			*tree = node;
	}
	return (tokens);
}

void	create_tree(t_token *tokens, t_tree **tree)
{
	while (tokens->value != NULL)
	{
		if (tokens->type == TOKEN_PIPE)
			tokens = parse_pipe(tree, tokens);
		else if (redir(tokens->type))
			tokens = parse_redirect(tree, tokens);
		else
			tokens = parse_cmd(tree, tokens);
	}
}