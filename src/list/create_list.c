/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:19:04 by atoof             #+#    #+#             */
/*   Updated: 2023/06/19 17:01:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// t_lst	*new_node(void)
// {
// 	t_lst	*node;

// 	node = malloc(sizeof(t_lst));
// 	node->args = NULL;
// 	node->cmd = NULL;
// 	node->next = NULL;
// 	node->file_name = NULL;
// 	node->type = 0;
// 	node->value = NULL;
// 	return (node);
// }

// // static void	init_node(void)
// static void	parse_pipe(t_lst **lst, t_token *tokens)
// {
// 	t_lst	*node;

// 	node = new_node();
// 	node->type = tokens->type;
// 	node->value = ft_strdup(tokens->value);
// 	ft_lstadd_back(lst, node);
// }

// static void	parse_redirect(t_lst **lst, t_token *tokens)
// {
// 	t_lst	*node;
// 	int		type;

// 	type = 0;
// 	type = tokens->type;
// 	node = new_node();
// 	node->type = tokens->type;
// 	node->value = ft_strdup(tokens->value);
// 	if (tokens->value)
// 		tokens++;
// 	node->file_name = ft_strdup(tokens->value);
// 	ft_lstadd_back(lst, node);
// 	if (tokens->value)
// 		tokens++;
// 	create_list(tokens);
// }

// static void	parse_cmd(t_lst **lst, t_token *tokens)
// {
// 	t_lst	*node;

// 	node = new_node();
// 	node->type = tokens->type;
// 	node->value = ft_strdup(tokens->value);
// 	ft_lstadd_back(lst, node);
// 	while (tokens->value)
// 	{
// 		tokens++;
// 		if (tokens->value && (tokens->type == TOKEN_ARG
// 				|| tokens->type == TOKEN_VARIABLE
// 				|| tokens->type == TOKEN_EXIT_STATUS))
// 			add_args(lst, tokens, new_node);
// 	}
// }

// t_lst	*create_list(t_token *tokens)
// {
// 	t_lst	*lst;

// 	if (!lst)
// 		lst = malloc(sizeof(t_lst));
// 	if (tokens->value != NULL)
// 	{
// 		if (tokens->type == TOKEN_PIPE)
// 			parse_pipe(&lst, tokens);
// 		else if (tokens->type == TOKEN_INPUT || tokens->type == TOKEN_OUTPUT
// 			|| tokens->type == TOKEN_HEREDOC
// 			|| tokens->type == TOKEN_OUTPUT_APPEND)
// 			parse_redirect(&lst, tokens);
// 		else
// 			parse_cmd(&lst, tokens);
// 	}
// }
