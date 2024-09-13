/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:34:00 by mtoof             #+#    #+#             */
/*   Updated: 2023/11/02 20:32:32 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phoenix.h"

char	*find_path(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = NULL;
	if (env != NULL)
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

	if (!*env)
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
