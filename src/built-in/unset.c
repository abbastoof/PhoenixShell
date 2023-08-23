/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/23 18:44:50 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_error(char *str)
{
	ft_putstr("Minishell: unset: `");
	if (str != NULL)
		ft_putstr(str);
	ft_putstr("': not a valid identifier\n");
	return (256);
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

int	ft_unset(t_tree *tree, t_env **env)
{
	int	index;
	int	flag;

	flag = 0;
	index = 1;
	if (*env != NULL)
	{
		while (index < tree->size_args)
		{
			if (tree->args[index] == NULL || ft_isdigit(tree->args[index][0]))
				flag = handle_error(tree->args[index]);
			else if (tree->args[index] != NULL && \
			ft_strchr(tree->args[index], '='))
				flag = handle_error(tree->args[index]);
			else
				free_key_env(env, tree->args[index]);
			index++;
		}
	}
	return (flag);
}
