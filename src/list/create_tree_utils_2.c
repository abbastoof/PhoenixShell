/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:14:41 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/01 23:40:52 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_redir **lst, t_redir *new)
{
	t_redir *last;

	last = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

void	parse_cmd_node(t_token **tokens, t_tree *node)
{
	if ((*tokens)->type == 0)
			(*tokens)->type = TOKEN_CMD;
	node->type = (*tokens)->type;
	node->cmd = ft_strdup((*tokens)->value);
	while ((*tokens)->value && (*tokens)->type != TOKEN_PIPE && (add_args(tokens, node)) == 1)
		(*tokens)++;
}
