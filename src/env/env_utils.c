/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/14 20:34:45 by atoof            ###   ########.fr       */
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

static int	str_env(t_env *tmp, char **env_ptr, int index)
{
	char	*join_equal_sign;

	if (tmp->key != NULL && tmp->value == NULL)
	{
		env_ptr[index] = ft_strdup(tmp->key);
		if (!env_ptr[index])
			return (-1);
	}
	else if (tmp->key != NULL && tmp->value != NULL)
	{
		join_equal_sign = ft_strjoin("=", tmp->value);
		if (!join_equal_sign)
			return (-1);
		else
		{
			env_ptr[index] = ft_strjoin(tmp->key, join_equal_sign);
			if (join_equal_sign != NULL)
				free(join_equal_sign);
			join_equal_sign = NULL;
		}
	}
	return (0);
}

char	**env_char_ptr(t_env **env, char **env_ptr)
{
	int		index;
	t_env	*tmp;

	if (!env)
		return (NULL);
	env_ptr = ft_calloc(sizeof(char *), ft_listsize(env) * 2);
	if (!env_ptr)
	{
		ft_putstr_fd("Malloc env_char_ptr\n", 2);
		return (NULL);
	}
	tmp = *env;
	index = 0;
	while (tmp != NULL)
	{
		str_env(tmp, env_ptr, index);
		if (!env_ptr[index])
			return (error_handling());
		index++;
		tmp = tmp->next;
	}
	return (env_ptr);
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
