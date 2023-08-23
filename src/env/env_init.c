/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:07:47 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 11:26:06 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*error_handling(void)
{
	ft_putstr_fd("Malloc\n", 2);
	return (NULL);
}

static int	init_node(char **split, t_env **node)
{
	if (split[0] != NULL)
	{
		(*node)->key = ft_strdup(split[0]);
		if (!(*node)->key)
			return (-1);
	}
	if (split[1] != NULL)
	{
		if (split[0] != NULL && ft_strncmp(split[0], "SHLVL", 6) == 0)
			(*node)->value = shelvl_value(split[1]);
		else if (split[0] != NULL && ft_strncmp(split[0], "OLDPWD", 6) == 0)
			(*node)->value = NULL;
		else
			(*node)->value = ft_strdup(split[1]);
		if (!(*node)->value && ft_strncmp(split[0], "OLDPWD", 6) != 0)
			return (-1);
	}
	else
		(*node)->value = NULL;
	return (0);
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

void	init_env(t_env **env, char **envp)
{
	t_env	*node;
	int		index;

	index = 0;
	while (envp[index] != NULL)
	{
		node = new_env_node(envp[index]);
		if (!node)
			exit(1);
		if (ft_strcmp(node->key, "_") == 0)
		{
			free(node->key);
			free(node->value);
			free(node);
			if (envp[index] != NULL)
				index++;
			continue ;
		}
		if (add_back_env(env, node) == -1)
			exit(1);
		if (envp[index] != NULL)
			index++;
	}
}
