/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/20 12:53:04 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shelvl_value(char *value)
{
	int	res;

	res = 0;
	if (value != NULL)
	{
		res = ft_atoi(value);
		res++;
		return (ft_itoa(res));
	}
	return (NULL);
}

int	add_back_env(t_env **lst, t_env *new_node)
{
	t_env	*last;

	last = *lst;
	if (!new_node)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new_node;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return (0);
}
