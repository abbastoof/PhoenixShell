/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/15 03:38:38 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir_node(t_token **tokens, int type)
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

int	parse_redir(t_token **tokens, t_tree *new_node)
{
	t_redir	*redir;

	redir = new_redir_node(tokens, (*tokens)->type);
	if (!redir)
		return (-1);
	if (!new_node->redir)
		new_node->redir = redir;
	else if (add_back(&new_node->redir, redir) == -1)
		return (-1);
	return (1);
}
