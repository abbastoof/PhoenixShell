/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:49:22 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/21 18:52:11 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_listsize(t_env **env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	if (!env)
		return (0);
	tmp = *env;
	while (tmp->next != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
