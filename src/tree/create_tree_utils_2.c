/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:14:41 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/12 17:00:52 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **args)
{
	int	index;

	index = 0;
	if (args[index] != NULL)
	{
		while (args[index])
		{
			free(args[index]);
			index++;
		}
		free(args);
	}
	args = NULL;
}

int	redir(int type)
{
	if (type >= TOKEN_INPUT && type <= TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_tree	*new_node(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
	{
		ft_putstr_fd("malloc new_node\n", 2);
		return (NULL);
	}
	node->type = 0;
	node->infile = 0;
	node->outfile = 0;
	node->count_in = 0;
	node->count_out = 0;
	node->cmd = NULL;
	node->args = NULL;
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

int	parse_cmd_node(t_token **tokens, t_tree *node)
{
	int	res;

	res = 0;
	if ((*tokens)->type == 0)
		(*tokens)->type = TOKEN_CMD;
	node->type = (*tokens)->type;
	node->cmd = ft_strdup((*tokens)->value);
	if (!node->cmd)
	{
		ft_putstr_fd("malloc strdup parse_cmd\n", 2);
		return (-1);
	}
	while ((*tokens)->value && (*tokens)->type != TOKEN_PIPE)
	{
		res = add_args(tokens, node);
		if (res > 0)
			(*tokens)++;
		else if (res == 0)
			break ;
		else
			return (-1);
	}
	return (0);
}
