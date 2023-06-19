/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:04:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/19 17:01:24 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	add_next_args(t_lst **list, t_token *tokens, t_lst *new_node,
// 		int size)
// {
// 	char	**new_args;

// 	new_args = NULL;
// 	if (new_node->args)
// 	{
// 		new_args = ft_realloc(new_node->args, size + 1);
// 		free(new_node->args);
// 		new_node->args = new_args;
// 		if (!new_node->args)
// 		{
// 			ft_putstr_fd("malloc\n", 2);
// 			//GO FOR FREE LINKLIST;
// 		}
// 		new_node->args[size] = ft_strdup(tokens->value);
// 		size++;
// 	}
// }

// void	add_args(t_lst **list, t_token *tokens, t_lst *new_node)
// {
// 	static int	size;

// 	if (tokens->type == TOKEN_ARG || tokens->type == TOKEN_VARIABLE
// 		|| tokens->type == TOKEN_EXIT_STATUS)
// 	{
// 		if (!new_node->args)
// 		{
// 			size = 2;
// 			new_node->args = ft_calloc(size, sizeof(char *));
// 			if (!new_node->args)
// 			{
// 				ft_putstr_fd("malloc\n", 2);
// 				//GO FOR FREE LINKLIST;
// 			}
// 			new_node->args = ft_strdup(tokens->value);
// 		}
// 		else
// 			add_next_args(list, tokens, new_node, size);
// 	}
// }
