/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:17:07 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/23 19:04:34 by mtoof            ###   ########.fr       */
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

static t_token	*parse_redirect(t_lst **tree, t_token *tokens)
{
	t_lst	*node;

	node = new_node();
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	//add file name to the node which is next node value
	if ((tokens + 1)->value)
	{
		tokens++;
		node->file_name = ft_strdup(tokens->value);
		if ((tokens + 1)->value)
			tokens++;
	}
	if ((*tree)->type != TOKEN_CMD)
		node->right = *tree;
	else
		node->left = *tree;
	*tree = node;
	return (tokens);
}

int	redir(int type)
{
	if (type >= 4 && type <= 7)
		return (1);
	return (0);
}

int	get_list_size(t_lst *tree)
{
	int		size;
	t_lst	*current;

	size = 0;
	current = tree;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	check_after_redir(t_lst **tree, t_token *tokens)
{
	int		size;
	t_lst	*last;
	t_lst	*new_node;

	size = get_list_size(*tree);
	last = *tree;
	while (last->next != NULL)
	{
		last = last->next;
		if (size > 0 && redir(last->type) && last->left->type == TOKEN_CMD)
		{
			new_node = malloc(sizeof(t_lst));
			new_node->args = tokens->value;
			last->next = new_node;
		}
	}
}

static t_token	*parse_cmd(t_lst **tree, t_token *tokens)
{
	t_lst	*node;

	if (redir((*tree)->type))
		check_after_redir(tree, tokens);
	node = new_node();
	if (tokens->type == 0)
		tokens->type = TOKEN_CMD;
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	while ((add_args(tokens, node)) == 1)
		tokens++;
	if (*tree && (*tree)->type == TOKEN_PIPE
		&& (*tree)->left->type == TOKEN_CMD)
		(*tree)->right = node;
	else if (*tree && redir((*tree)->type) && (*tree)->left->type == TOKEN_CMD)
	{
		(*tree)->left->args = tokens->value;
	}
	else if (*tree && !(*tree)->left)
		(*tree)->left = node;
	else
		*tree = node;
	return (tokens);
}

void	create_list(t_token *tokens, t_lst **tree)
{
	int	indx;

	indx = 0;
	while (tokens->value != NULL)
	{
		if (tokens->type == TOKEN_PIPE)
			tokens = parse_pipe(tree, tokens);
		else if (tokens->type == TOKEN_INPUT || tokens->type == TOKEN_OUTPUT
				|| tokens->type == TOKEN_HEREDOC
				|| tokens->type == TOKEN_OUTPUT_APPEND)
			tokens = parse_redirect(tree, tokens);
		else
			tokens = parse_cmd(tree, tokens);
	}
}
