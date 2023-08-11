/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:14:41 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/11 14:00:40 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(int type)
{
	if (type >= TOKEN_INPUT && type <= TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_tree	*new_tree_node(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
	{
		ft_putstr_fd("malloc new_node\n", 2);
		return (NULL);
	}
	node->type = 0;
	node->fd_out = 0;
	node->fd_in = 0;
	node->count_in = 0;
	node->count_out = 0;
	node->cmd = NULL;
	node->args = NULL;
	node->cmd_paths = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	last = *lst;
	if (!lst || !new)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (0);
}
