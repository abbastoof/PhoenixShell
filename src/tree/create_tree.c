/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:19:04 by atoof             #+#    #+#             */
/*   Updated: 2023/06/15 18:00:16 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_tree(t_token *tokens)
{
	t_tree *tree;
	int		i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_PIPE)
			parse_pipe(&tree, tokens[i]);
		else if (tokens[i].type == TOKEN_INPUT || tokens[i].type == TOKEN_OUTPUT)
			parse_redirect(&tree, tokens[i]);
		else if (tokens[i].type == TOKEN_HEREDOC)
			parse_heredoc();
		else if (tokens[i].type == TOKEN_CMD)
			parse_cmd(&tree, tokens, i);
	}
}