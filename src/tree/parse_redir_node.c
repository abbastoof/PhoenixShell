/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/17 18:09:17 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*error_msg(void)
{
	ft_putstr_fd("malloc redir node\n", 2);
	return (NULL);
}

static void	heredoc_filename(t_token **tokens, char *index, t_redir **new)
{
	char	*fd;

	fd = NULL;
	fd = ft_strjoin((*tokens)->value, index);
	if (!fd)
		return ;
	(*new)->file_name = ft_strdup(fd);
	if (fd)
	{
		free(fd);
		fd = NULL;
	}
	(*new)->key = ft_strdup((*tokens)->value);
}

t_redir	*new_redir_node(t_token **tokens, int type, char *index)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (error_msg());
	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		(*tokens) = (*tokens)->next;
		heredoc_filename(tokens, index, &new);
	}
	else
	{
		(*tokens) = (*tokens)->next;
		new->file_name = ft_strdup((*tokens)->value);
		new->key = NULL;
	}
	if (!new->file_name)
		return (error_msg());
	new->type = type;
	new->last = 0;
	new->next = NULL;
	return (new);
}

int	parse_redir(t_token **tokens, t_tree *new_node)
{
	t_redir		*redir;
	static int	index;
	char		*index_ptr;

	index++;
	index_ptr = NULL;
	index_ptr = ft_itoa(index);
	redir = new_redir_node(tokens, (*tokens)->type, index_ptr);
	if (index_ptr)
	{
		free(index_ptr);
		index_ptr = NULL;
	}
	if (!redir)
		return (-1);
	if (!new_node->redir)
		new_node->redir = redir;
	else if (add_back(&new_node->redir, redir) == -1)
		return (-1);
	return (1);
}
