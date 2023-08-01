/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:05:33 by atoof             #+#    #+#             */
/*   Updated: 2023/07/31 16:56:58 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	ft_free_strarray(char **str_array)
{
	char	**temp;

	if (str_array == NULL)
		return ;
	temp = str_array;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(str_array);
}

char	*find_path(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0)
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
