/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:19:04 by atoof             #+#    #+#             */
/*   Updated: 2023/06/23 16:16:04 by mtoof            ###   ########.fr       */
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
	node->file_name = NULL;
	node->type = 0;
	node->value = NULL;
	return (node);
}

static t_token	*parse_pipe(t_lst **lst, t_token *tokens)
{
	t_lst	*node;

	node = new_node();
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	add_back(lst, node);
	if ((tokens + 1)->value)
		tokens++;
	return (tokens);
}

static t_token	*parse_redirect(t_lst **lst, t_token *tokens)
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
	}
	tokens++;
	// tokens = add_remainder_as_args(lst, tokens);
	add_back(lst, node);
	return (tokens);
}

static t_token	*parse_cmd(t_lst **lst, t_token *tokens)
{
	t_lst	*node;

	node = new_node();
	if (tokens->type == 0)
		tokens->type = TOKEN_CMD;
	node->type = tokens->type;
	node->value = ft_strdup(tokens->value);
	while ((add_args(tokens, node)) == 1)
		tokens++;
	add_back(lst, node);
	return (tokens);
}

void	create_list(t_token *tokens, t_lst **lst)
{
	while (tokens->value != NULL)
	{
		if (tokens->type == TOKEN_PIPE)
			tokens = parse_pipe(lst, tokens);
		else if (tokens->type == TOKEN_INPUT || tokens->type == TOKEN_OUTPUT
			|| tokens->type == TOKEN_HEREDOC
			|| tokens->type == TOKEN_OUTPUT_APPEND)
			tokens = parse_redirect(lst, tokens);
		else
			tokens = parse_cmd(lst, tokens);
	}
}
