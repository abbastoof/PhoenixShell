/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_delete_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/01 18:57:21 by atoof            ###   ########.fr       */
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

void	display_list(t_tree *lst)
{
	if (lst->left && lst->left->type == TOKEN_PIPE)
		display_list(lst->left);
	if(lst && lst->left && lst->left->type == TOKEN_CMD)
	{
		printf("cmd = %s\n", lst->left->cmd);
		int i = 0;
		if (lst->left->args)
		{
			while (lst->left->args[i])
			{
				printf("args = %s\n", lst->left->args[i]);
				i++;
			}
		}
		if (lst->left->redir)
		{
			while(lst->left->redir)
			{
				printf("redir_type = %d\n", lst->left->redir->type);
				printf("redir_type = %s\n", lst->left->redir->file_name);
				lst->left->redir = lst->left->redir->next;
			}
		}
	}
	if(lst && lst->right && lst->right->type == TOKEN_CMD)
	{
		printf("cmd = %s\n", lst->cmd);
		int i = 0;
		while (lst->right->args[i])
		{
			printf("args = %s\n", lst->right->args[i]);
			i++;
		}
		while(lst->right->redir)
		{
			printf("redir_type = %d\n", lst->right->redir->type);
			printf("redir_type = %s\n", lst->right->redir->file_name);
			lst->right->redir = lst->right->redir->next;
		}
	}
	else
	{
		printf("cmd = %s\n", lst->cmd);
		int i = 0;
		if (lst->args)
		{
			while (lst->args[i])
			{
				printf("args = %s\n", lst->args[i]);
				i++;
			}
		}
		while(lst->redir != NULL)
		{
			printf("redir_type = %d\n", lst->redir->type);
			printf("redir_type = %s\n", lst->redir->file_name);
			lst->redir = lst->redir->next;
		}
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

