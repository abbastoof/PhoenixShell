/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_delete_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/01 23:47:35 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_cmd_args(t_lst *lst)
// {
// 	int	i;

// 	printf("cmd = %s\n", lst->value);
// 	if (lst->args)
// 	{
// 		i = 0;
// 		while (lst->args[i])
// 		{
// 			printf("cmd.args = %s\n", lst->args[i]);
// 			i++;
// 		}
// 	}
// }

void	print_node(t_tree *lst)
{
	int	i;

	printf("cmd = %s\n", lst->cmd);
	i = 0;
	while (lst->args[i])
	{
		printf("args = %s\n", lst->args[i]);
		i++;
	}
	while(lst->redir)
	{
		printf("redir_type = %d\n", lst->redir->type);
		printf("file_name = %s\n", lst->redir->file_name);
		lst->redir = lst->redir->next;
	}
}

void	display_list(t_tree *lst)
{
	if (lst->left && lst->left->type == TOKEN_PIPE)
	{
			display_list(lst->left);
			printf("pipe\n");
	}
	if(lst && (lst->left && lst->left->type == TOKEN_CMD) && (lst->right && lst->right->type == TOKEN_CMD))
	{
		printf("first pipe\n");
		printf("left->cmd = %s\n", lst->left->cmd);
		print_node(lst->left);
		printf("right->cmd = %s\n", lst->right->cmd);
		print_node(lst->right);
	}
	if(lst && lst->left->type == TOKEN_PIPE && lst->right && lst->right->type == TOKEN_CMD)
	{
		print_node(lst->right);
	}
}

// void	free_list(t_lst *lst)
// {
// 	int	indx;

// 	indx = 0;
// 	if (lst != NULL)
// 	{
// 		while (lst->value != NULL)
// 		{
// 			if (lst->type == TOKEN_CMD || lst->type == TOKEN_EXIT_STATUS)
// 			{
// 				free(lst->value);
// 				while (lst->args[indx])
// 				{
// 					free(lst->args[indx]);
// 					indx++;
// 				}
// 			}
// 			else if (lst->type == TOKEN_PIPE)
// 				free(lst->value);
// 			else
// 			{
// 				free(lst->value);
// 				free(lst->file_name);
// 			}
// 			if (lst->next == NULL)
// 				break ;
// 			lst = lst->next;
// 		}
// 	}
// }



// void	execute_tree(t_tree *tree)
// {
// 	if (tree->right)
// 		execute_tree(tree->right);
// 	if(tree->left)
// 		execute_tree(tree->left);
// }

// void	execute_tree(t_tree *tree)
// {
// 	if (tree->right)
// 		execute_tree(tree->right);
// 	if(tree->left)
// 		execute_tree(tree->left);//
// }

