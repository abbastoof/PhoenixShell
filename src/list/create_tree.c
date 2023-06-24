/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:17:07 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/24 16:22:41 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lst	*new_node(void)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	node->args = NULL;
	node->cmd = NULL;
	node->next = NULL;
	node->right = NULL;
	node->left = NULL;
	node->file_name = NULL;
	node->type = 0;
	node->value = NULL;
	return (node);
}

static t_token	*parse_pipe(t_lst **tree, t_token *tokens)
{
	t_lst	*node;

	node = new_node();
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	if ((*tree) && (*tree)->type == TOKEN_CMD)
		node->left = *tree;
	else
		node->right = *tree;
	*tree = node;
	tokens++;
	return (tokens);
}

t_token	*add_remainder(t_token *tokens, t_lst **tree)
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

static t_token	*parse_redirect(t_lst **tree, t_token *tokens)
{
	t_lst	*node;

	if ((*tree) && (*tree)->left && (*tree)->value == NULL && (*tree)->type == 0)
	{
		(*tree)->type = tokens->type;
		(*tree)->value = ft_strdup(tokens->value);
		if ((tokens + 1)->value)
		{
			tokens++;
			(*tree)->file_name = ft_strdup(tokens->value);
		}
	}
	else
	{
		node = new_node();
		node->type = tokens->type;
		node->value = ft_strdup(tokens->value);
	//add file name to the node which is next node value
		if ((tokens + 1)->value)
		{
			tokens++;
			node->file_name = ft_strdup(tokens->value);
		}
		if ((*tree) && (*tree)->type != TOKEN_CMD)
			node->right = *tree;
		else
			node->left = *tree;
		*tree = node;
	}
	tokens++;
	tokens = add_remainder(tokens, tree);
	return (tokens);
}

// int	get_list_size(t_lst *tree)
// {
// 	int		size;
// 	t_lst	*current;

// 	size = 0;
// 	current = tree;
// 	while (current != NULL)
// 	{
// 		size++;
// 		current = current->next;
// 	}
// 	return (size);
// }

// void	check_after_redir(t_lst **tree, t_token *tokens)
// {
// 	int		size;
// 	t_lst	*last;
// 	t_lst	*new_node;

// 	size = get_list_size(*tree);
// 	last = *tree;
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 		if (size > 0 && redir(last->type) && last->left->type == TOKEN_CMD)
// 		{
// 			new_node = malloc(sizeof(t_lst));
// 			new_node->args = tokens->value;
// 			last->next = new_node;
// 		}
// 	}
// }

static t_token	*parse_cmd(t_lst **tree, t_token *tokens)
{
	t_lst	*node;
	t_lst	*tmp;

	node = new_node();
	if (tokens->type == 0)
		tokens->type = TOKEN_CMD;
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	while (tokens->value && (!redir(tokens->type) && tokens->type!= TOKEN_PIPE) && (add_args(tokens, node)) == 1)
		tokens++;
	//if we have a redirector or a pipe with a left then we create a new empty node and point its right to the tree
	//and left of that point to the *node
	//In the past if we had "cmd1 args | cmd2 args2 >out" the cmd2 would go to the right of the pipe
	//I added a simple code to the beginning of the parse_redir because the tmp_node in here doesn't have type nor value 
	// so before create a new node in parse_redir if the current node has left and doesn't have type or value we add the 
	// value and type of the redirector to the tmp node and no need to create a node for the redirector because it's already been created 
	if (*tree && (*tree)->left)
	{
		tmp = new_node();
		tmp->right = *tree;
		tmp->left = node;
		*tree = tmp;
	}
	else if (*tree && !(*tree)->left)
		(*tree)->left = node;
	else
		*tree = node;
	return (tokens);
}

void	create_list(t_token *tokens, t_lst **tree)
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
