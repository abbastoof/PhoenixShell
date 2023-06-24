/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_delete_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/24 16:06:22 by mtoof            ###   ########.fr       */
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

void	display_list(t_lst *lst)
{
	if (lst->right)
	{

		display_list(lst->right);
		printf("redirector = %s\n", lst->value);
		printf("file_name = %s\n", lst->file_name);
	}
	if (lst->left != NULL)
	{
		// printf("redirector = %s\n", lst->value);
		// if (lst->file_name)
		// 	printf("file_name = %s\n", lst->file_name);
		printf("left = %s\n", lst->left->value);
		int i = 0;
		while (lst->left->args[i])
		{
			printf("args = %s\n", lst->left->args[i]);
			i++;
		}
	}
}

void	free_list(t_lst *lst)
{
	int	indx;

	indx = 0;
	if (lst != NULL)
	{
		while (lst->value != NULL)
		{
			if (lst->type == TOKEN_CMD || lst->type == TOKEN_EXIT_STATUS)
			{
				free(lst->value);
				while (lst->args[indx])
				{
					free(lst->args[indx]);
					indx++;
				}
			}
			else if (lst->type == TOKEN_PIPE)
				free(lst->value);
			else
			{
				free(lst->value);
				free(lst->file_name);
			}
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
	}
}



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

