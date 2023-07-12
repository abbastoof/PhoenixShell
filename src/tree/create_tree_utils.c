/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/12 13:45:41 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_node(t_token **tokens, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
	{
		ft_putstr_fd("malloc redir node\n", 2);
		return (NULL);
	}
	(*tokens)++;
	new->file_name = ft_strdup((*tokens)->value);
	if (!new->file_name)
	{
		ft_putstr_fd("malloc redir node file_name\n", 2);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

static int	add_next_args(t_token *tokens, t_tree *new_node, int size)
{
	char	**new_args;
	int		indx;

	indx = 0;
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

static int	parse_redir(t_token **tokens, t_tree *new_node)
{
	t_redir	*redir;

	redir = redir_node(tokens, (*tokens)->type);
	if (!redir)
		return (-1);
	if (!new_node->redir)
		new_node->redir = redir;
	else if (add_back(&new_node->redir, redir) == -1)
		return (-1);
	return (1);
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
	new_node->args[0] = ft_strdup((*tokens)->value);
	if (!new_node->args[0])
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
