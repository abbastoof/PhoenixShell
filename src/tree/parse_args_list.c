/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:49:03 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/18 21:55:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*new_args_node(char *str)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
	{
		ft_putstr_fd("malloc realloc add_args\n", 2);
		return (NULL);
	}
	if (str != NULL)
	{
		new->value = ft_strdup(str);
		if (!new->value)
		{
			ft_putstr_fd("Malloc new->value\n", 2);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

int	args_add_back(t_args **args, t_args *new)
{
	t_args	*last;

	last = *args;
	if (!args || !new)
		return (-1);
	if (*args == NULL)
	{
		*args = new;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (0);
}

void	free_args_list(t_args **args, t_tree *node)
{
	t_args	*head;
	int		index;

	index = 0;
	if (!args)
		return ;
	head = *args;
	while (*args != NULL)
	{
		head = (*args)->next;
		if (index < node->size_args)
		{
			if ((*args)->value != NULL)
			{
				free((*args)->value);
				(*args)->value = NULL;
			}
			index++;
		}
		free((*args));
		(*args) = head;
	}
}
