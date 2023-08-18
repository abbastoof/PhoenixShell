/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:14:41 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/17 20:05:32 by mtoof            ###   ########.fr       */
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
	node->args_ptr = NULL;
	node->size_args = 0;
	node->type = 0;
	node->fd_out = 0;
	node->fd_in = 0;
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

static int	malloc_args_char_ptr(t_tree *node)
{
	t_args	*tmp;

	tmp = node->args_ptr;
	while (tmp != NULL)
	{
		node->size_args++;
		tmp = tmp->next;
	}
	if (node->args == NULL)
	{
		node->args = ft_calloc(sizeof(char *), node->size_args + 1);
		if (!node->args)
		{
			ft_putstr_fd("Malloc add_args_list\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	add_args_list(t_tree *node)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = node->args_ptr;
	if (malloc_args_char_ptr(node) == -1)
		return (-1);
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			node->args[i] = ft_strdup(tmp->value);
			if (!node->args[i])
			{
				ft_putstr_fd("Malloc add_args_list\n", 2);
				return (-1);
			}
		}
		else
			node->args[i] = NULL;
		i++;
		tmp = tmp->next;
	}
	return (0);
}
