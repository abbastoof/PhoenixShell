/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:53:11 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/19 22:13:29 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd_args(t_lst *lst)
{
	int	i;

	printf("cmd = %s\n", lst->value);
	if (lst->args)
	{
		i = 0;
		while (lst->args[i])
		{
			printf("cmd.args = %s\n", lst->args[i]);
			i++;
		}
	}
}

void	display_list(t_lst *lst)
{
	if (lst != NULL)
	{
		while (lst->value != NULL)
		{
			if (lst->type == TOKEN_CMD || lst->type == TOKEN_EXIT_STATUS)
				print_cmd_args(lst);
			else if (lst->type == TOKEN_PIPE)
				printf("pipe = %s\n", lst->value);
			else
			{
				printf("redirector = %s\n", lst->value);
				printf("file_name = %s\n", lst->file_name);
			}
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
	}
}
