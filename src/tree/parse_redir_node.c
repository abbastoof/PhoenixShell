/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/09 18:36:04 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*error_msg(void)
{
	ft_putstr_fd("malloc redir node\n", 2);
	return (NULL);
}

t_redir	*new_redir_node(t_token **tokens, int type, char *index)
{
	t_redir	*new;
	char	*fd;

	fd = NULL;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (error_msg());
	(*tokens)++;
	fd = ft_strjoin((*tokens)->value, index);
	if (!fd)
		return (error_msg());
	new->file_name = ft_strdup(fd);
	if (!new->file_name)
		return (error_msg());
	new->type = type;
	new->last = 0;
	new->next = NULL;
	return (new);
}

int	redir_size(t_redir *lst)
{
	int		size;
	t_redir	*tmp;

	size = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

int	parse_redir(t_token **tokens, t_tree *new_node)
{
	t_redir		*redir;
	int			lst_size;
	t_redir		*tmp;

	tmp = new_node->redir;
	lst_size = redir_size(tmp);
	redir = new_redir_node(tokens, (*tokens)->type, ft_itoa(lst_size));
	if (!redir)
		return (-1);
	if (!new_node->redir)
		new_node->redir = redir;
	else if (add_back(&new_node->redir, redir) == -1)
		return (-1);
	return (1);
}
