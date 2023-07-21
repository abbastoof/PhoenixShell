/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/21 18:45:37 by mtoof            ###   ########.fr       */
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

static void	*error_handling(void)
{
	ft_putstr_fd("Malloc env_char_ptr\n", 2);
	return (NULL);
}

char	**env_char_ptr(t_env **env)
{
	char	**ptr;
	int		index;
	t_env	*tmp;

	if (!env)
		return (NULL);
	ptr = ft_calloc(sizeof(char *), ft_listsize(env));
	if (!ptr)
		return (NULL);
	tmp = *env;
	index = 0;
	while (tmp != NULL)
	{
		if (tmp->key != NULL && tmp->value == NULL)
		{
			ptr[index] = ft_strdup(tmp->key);
			if (!ptr[index])
				return (error_handling());
		}
		else if (tmp->key != NULL && tmp->value != NULL)
		{
			ptr[index] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value));
			if (!ptr[index])
				return (error_handling());
		}
		index++;
		tmp = tmp->next;
	}

	return (ptr);
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
