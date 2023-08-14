/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 15:43:07 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_error(char *str)
{
	ft_putstr("Minishell: unset: `");
	ft_putstr(str);
	ft_putstr("': not a valid identifier\n");
	return (1);
}

static void	free_node(t_env **node, t_env **prev)
{
	(*prev)->next = (*node)->next;
	if ((*node)->key != NULL)
		free((*node)->key);
	if ((*node)->value != NULL)
		free((*node)->value);
	(*node)->key = NULL;
	(*node)->value = NULL;
	free((*node));
	(*node) = NULL;
}

static void	delete_from_head(t_env **env, t_env **tmp)
{
	*env = (*env)->next;
	if ((*tmp)->key != NULL)
		free((*tmp)->key);
	if ((*tmp)->value != NULL)
		free((*tmp)->value);
	(*tmp)->key = NULL;
	(*tmp)->value = NULL;
	free((*tmp));
}

int	free_key_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env)
		return (0);
	tmp = *env;
	prev = *env;
	if (key != NULL && tmp->key != NULL && ft_strcmp(tmp->key, key) == 0)
	{
		delete_from_head(env, &tmp);
		return (0);
	}
	while (tmp != NULL && tmp->key != NULL && ft_strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	free_node(&tmp, &prev);
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	index;
	int	flag;

	flag = 0;
	index = 1;
	if (*env != NULL)
	{
		while (args[index] != NULL)
		{
			if (ft_isdigit(args[index][0]))
				flag = handle_error(args[index]);
			if (ft_strchr(args[index], '='))
				flag = handle_error(args[index]);
			else
				free_key_env(env, args[index]);
			index++;
		}
	}
	return (flag);
}
