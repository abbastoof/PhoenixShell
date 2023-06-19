/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/19 22:10:10 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_next_args(t_token *tokens, t_lst *new_node, int size)
{
	char	**new_args;

	new_args = NULL;
	if (new_node->args)
	{
		new_args = ft_realloc(new_node->args, size + 1);
		if (!new_args)
		{
			ft_putstr_fd("malloc\n", 2);
			//GO FOR FREE LINKLIST;
		}
		free(new_node->args);
		new_node->args = NULL;
		new_node->args = new_args;
		new_node->args[size - 1] = ft_strdup(tokens->value);
		size++;
	}
	return (size);
}

int	add_args(t_token *tokens, t_lst *new_node)
{
	static int	size;

	if (tokens->type == TOKEN_ARG || tokens->type == TOKEN_VARIABLE
		|| tokens->type == TOKEN_EXIT_STATUS || tokens->type == TOKEN_CMD)
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
			new_node->args[0] = ft_strdup(tokens->value);
		}
		else
			size = add_next_args(tokens, new_node, size);
		return (1);
	}
	return (0);
}
