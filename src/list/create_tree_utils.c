/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/01 21:36:51 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_node(t_token **tokens, int type)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	(*tokens)++;
	new->file_name = ft_strdup((*tokens)->value);
	new->type = type;
	new->next = NULL;
	return (new);
}

int	redir(int type)
{
	if (type >= TOKEN_INPUT && type <= TOKEN_HEREDOC)
		return (1);
	return (0);
}

static int	add_next_args(t_token *tokens, t_tree *new_node, int size)
{
	char	**new_args;

	new_args = NULL;
	if (new_node->args)
	{
		new_args = ft_realloc(new_node->args, ++size);
		if (!new_args)
		{
			ft_putstr_fd("malloc\n", 2);
			//GO FOR FREE LINKLIST;
		}
		free(new_node->args);
		new_node->args = NULL;
		new_node->args = new_args;
		new_node->args[size - 2] = ft_strdup(tokens->value);
	}
	return (size);
}

static void parse_redir(t_token **tokens, t_tree *new_node)
{
	t_redir *redir;

	redir = redir_node(tokens, (*tokens)->type);
	//protect_malloc
	if (!new_node->redir)
		new_node->redir = redir;
	else
		add_back(&new_node->redir, redir);
}

int	add_args(t_token **tokens, t_tree *new_node)
{
	static int	size;

	if ((*tokens)->type != TOKEN_PIPE)
	{
		if (redir((*tokens)->type))
			parse_redir(tokens, new_node);
		else
		{
			if (!new_node->args)
			{
				size = 2;
				new_node->args = ft_calloc(size, sizeof(char *));
				if (!new_node->args)
				{
					ft_putstr_fd("malloc\n", 2);
					//GO FOR FREE LINKLIST;
				}
				new_node->args[0] = ft_strdup((*tokens)->value);
			}
			else
				size = add_next_args((*tokens), new_node, size);
		}
		return (1);
	}
	return (0);
}
