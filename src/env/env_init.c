/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:07:47 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/19 11:56:07 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	*error_handling(void)
// {
// 	ft_putstr_fd("Malloc\n", 2);
// 	return (NULL);
// }

// t_env	*new_node(char *line)
// {
// 	char	**split;
// 	t_env	*new;

// 	split = ft_split(line, '=');
// 	if (!split)
// 		return (error_handling());
// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return (error_handling());
// 	new->key = split[0];
// 	new->value = split[1];
// 	new->next = NULL;
// }

// int	add_back(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	last = *lst;
// 	if (!new)
// 		return (-1);
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return (0);
// 	}
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = new;
// 	return (0);
// }

// void	init_env(t_env *env, char **envp)
// {
// 	t_env	*node;
// 	int		index;

// 	index = 0;
// 	while (envp[index] != NULL)
// 	{
// 		node = new_node(envp[index]);
// 		if (!node)
// 			exit(1);
// 		if (add_back(&env, envp[index]) == -1)
// 			exit(1);
// 		index++;
// 	}
// }
