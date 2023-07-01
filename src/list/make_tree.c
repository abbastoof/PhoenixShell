/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:31:15 by atoof             #+#    #+#             */
/*   Updated: 2023/07/01 18:47:54 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static t_tree	*new_node(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->type = 0;
	node->cmd = NULL;
	node->args = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_token	*parse_pipe(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	node = new_node();
	node->type = tokens->type;
	if ((*tree))
		node->left = *tree;
	// else
	// 	node->right = *tree;
	*tree = node;
	tokens++;
	return (tokens);
}

t_token	*add_remainder(t_token *tokens, t_tree **tree)
{
	//must have a cmd on the left to get here
	if (tokens->value && (*tree)->left && !(redir(tokens->type)) && tokens->type != TOKEN_PIPE)
	{
		while (tokens->value && (add_args(tokens, (*tree)->left) == 1))
			tokens++;
	}
	// if we don't have left (or cmd) then recersive call the function and this time we send tree->right
	if ((*tree)->left == NULL)
		tokens = add_remainder(tokens, &(*tree)->right);
	return (tokens);
}

static t_token	*parse_redirect(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	if(*tree && redir((*tree)->type))
	{
		add_back(&(*tree)->redir,redir_node(&tokens, tokens->type));
	}
	else
	{
		node = new_node();
		node->type = tokens->type;
		tokens++;
		node->redir = redir_node(&tokens, tokens->type);
		if (*tree && (*tree)->left && (*tree)->left->type == TOKEN_PIPE && !(*tree)->right)
			(*tree)->right = node;
		else
			(*tree) = node;
	} 
	tokens++;
	// tokens = add_remainder(tokens, tree);
	return (tokens);
}

static t_token	*parse_cmd(t_tree **tree, t_token *tokens)
{
	t_tree	*node;

	if ((*tree && redir((*tree)->type)))
	{
		// node = new_node();
		if (tokens->type == 0)
			tokens->type = TOKEN_CMD;
		(*tree)->type = tokens->type;
		(*tree)->cmd = ft_strdup(tokens->value);
		while (tokens->value && tokens->type != TOKEN_PIPE && (add_args(tokens, (*tree))) == 1)
			tokens++;
	}
	else if (*tree && (*tree)->right && redir((*tree)->right->type))
	{
		if (tokens->type == 0)
			tokens->type = TOKEN_CMD;
		(*tree)->right->type = tokens->type;
		(*tree)->right->cmd = ft_strdup(tokens->value);
		while (tokens->value && tokens->type != TOKEN_PIPE && (add_args(tokens, (*tree)->right)) == 1)
			tokens++;
	}
	else
	{
		node = new_node();
		if (tokens->type == 0)
			tokens->type = TOKEN_CMD;
		node->type = tokens->type;
		node->cmd = ft_strdup(tokens->value);
		while (tokens->value && tokens->type != TOKEN_PIPE && (add_args(tokens, node)) == 1)
			tokens++;
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