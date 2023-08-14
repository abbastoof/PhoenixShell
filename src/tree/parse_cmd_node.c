/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:33:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/14 13:25:58 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_next_args(t_token *tokens, t_tree *new_node, int size)
{
	char	**new_args;

	new_args = NULL;
	if (new_node->args != NULL)
	{
		new_args = ft_realloc(new_node->args, ++size);
		if (!new_args)
		{
			ft_putstr_fd("malloc realloc add_args\n", 2);
			return (-1);
		}
		if (new_node->args)
			free_double_ptr(new_node->args);
		new_node->args = new_args;
		new_node->args[size - 2] = ft_strdup(tokens->value);
		if (!new_node->args[size - 2])
		{
			ft_putstr_fd("malloc str_dup add_args\n", 2);
			return (-1);
		}
	}
	return (size);
}

static int	add_cmd_to_args_dbl_ptr(t_token **tokens, t_tree *new_node)
{
	int	size;

	size = 2;
	new_node->args = ft_calloc(size, sizeof(char *));
	if (!new_node->args)
	{
		ft_putstr_fd("malloc add_cmd_args\n", 2);
		return (-1);
	}
	if (!new_node->cmd)
		new_node->cmd = ft_strdup((*tokens)->value);
	new_node->args[0] = ft_strdup((*tokens)->value);
	if (!new_node->args[0] || !new_node->cmd)
	{
		ft_putstr_fd("malloc strdup add_cmd_args\n", 2);
		return (-1);
	}
	return (size);
}

int	add_args(t_token **tokens, t_tree *new_node)
{
	static int	size;

	if ((*tokens)->type != TOKEN_PIPE)
	{
		if (redir((*tokens)->type))
			return (parse_redir(tokens, new_node));
		else
		{
			if (!new_node->args)
			{
				size = add_cmd_to_args_dbl_ptr(tokens, new_node);
				if (size == -1)
					return (-1);
			}
			else
			{
				size = add_next_args((*tokens), new_node, size);
				if (size == -1)
					return (-1);
			}
		}
		return (1);
	}
	return (0);
}

static void	init_node_cmd(t_token **tokens, t_tree *node)
{
	if ((*tokens)->type == 0)
		(*tokens)->type = TOKEN_CMD;
	node->type = TOKEN_CMD;
	node->cmd = ft_strdup((*tokens)->value);
}

int	parse_cmd_node(t_token **tokens, t_tree *node)
{
	int	res;

	res = 0;
	if (redir((*tokens)->type) == 0)
	{
		init_node_cmd(tokens, node);
		if (!node->cmd)
		{
			ft_putstr_fd("malloc strdup parse_cmd\n", 2);
			return (-1);
		}
	}
	while ((*tokens)->value && (*tokens)->type != TOKEN_PIPE)
	{
		res = add_args(tokens, node);
		if (res > 0)
			(*tokens)++;
		else if (res == 0)
			break ;
		else
			return (-1);
	}
	return (0);
}
