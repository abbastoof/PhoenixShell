/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:34:00 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/18 22:34:14 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_env(t_env **env)
{
	t_env	*head;

	if (!env)
		return ;
	head = *env;
	while (*env != NULL)
	{
		head = (*env)->next;
		if ((*env)->key != NULL)
			free((*env)->key);
		if ((*env)->value != NULL)
			free((*env)->value);
		(*env)->value = NULL;
		(*env)->key = NULL;
		free((*env));
		(*env) = head;
	}
}
