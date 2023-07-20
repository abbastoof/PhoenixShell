/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/20 12:35:31 by mtoof            ###   ########.fr       */
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

t_env	*new_env_node(char *line)
{
	char	**split;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (error_handling());
	split = ft_split(line, '=');
	if (!split)
		return (error_handling());
	if (init_node(split, &node) == -1)
		return (error_handling());
	node->next = NULL;
	if (split)
		free_double_ptr(split);
	return (node);
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
