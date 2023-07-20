/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 16:00:20 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (tmp->key != NULL)
		{
			if (tmp->key && tmp->value)
			{
				ft_putstr_fd(tmp->key, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		tmp = tmp->next;
	}
}
