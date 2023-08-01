/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/31 12:56:39 by mtoof            ###   ########.fr       */
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

static char	*str_env(t_env *tmp)
{
	char	*join_equal_sign;

	if (tmp->key != NULL && tmp->value == NULL)
		return (ft_strdup(tmp->key));
	else if (tmp->key != NULL && tmp->value != NULL)
	{
		join_equal_sign = ft_strjoin("=", tmp->value);
		if (!join_equal_sign)
			return (NULL);
		else
			return (ft_strjoin(tmp->key, join_equal_sign));
	}
	return (NULL);
}

char	**env_char_ptr(t_env **env)
{
	char	**ptr;
	int		index;
	t_env	*tmp;

	if (!env)
		return (NULL);
	ptr = ft_calloc(sizeof(char *), ft_listsize(env) + 1);
	if (!ptr)
		return (NULL);
	tmp = *env;
	index = 0;
	while (tmp != NULL)
	{
		ptr[index] = str_env(tmp);
		if (!ptr[index])
			return (error_handling());
		index++;
		tmp = tmp->next;
	}

	return (ptr);
}

int	add_back_env(t_env **env, t_env *new_node)
{
	t_env	*last;

	last = *env;
	if (!new_node)
		return (-1);
	if (*env == NULL)
	{
		*env = new_node;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return (0);
}
