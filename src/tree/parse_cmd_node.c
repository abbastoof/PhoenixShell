/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:33:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 18:12:01 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_args_to_list(t_tree *new_node, t_token **tokens)
{
	t_args		*new;

	new = NULL;
	new = new_args_node((*tokens)->value);
	if (!new)
		return (-1);
	if (!new_node->args_ptr)
		new_node->args_ptr = new;
	else if (args_add_back(&new_node->args_ptr, new) == -1)
		return (-1);
	return (0);
}

int	add_args(t_token **tokens, t_tree *new_node)
{
	if ((*tokens)->type != TOKEN_PIPE)
	{
		if (redir((*tokens)->type))
			return (parse_redir(tokens, new_node));
		else
		{
			if (new_node->cmd == NULL)
			{
				if ((*tokens)->value != NULL)
				{
					new_node->cmd = ft_strdup((*tokens)->value);
					if (!new_node->cmd)
						return (-1);
				}
			}
			if (add_args_to_list(new_node, tokens) == -1)
				return (-1);
		}
		return (1);
	}
	return (0);
}

int	parse_cmd_node(t_token **tokens, t_tree *node)
{
	int	res;

	res = 0;
	while ((*tokens) != NULL && (*tokens)->type != TOKEN_PIPE)
	{
		res = add_args(tokens, node);
		if (res > 0)
			(*tokens) = (*tokens)->next;
		else if (res == 0)
			break ;
		else
			return (-1);
	}
	return (0);
}
