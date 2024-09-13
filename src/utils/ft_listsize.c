/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:49:22 by mtoof             #+#    #+#             */
/*   Updated: 2023/11/02 20:29:02 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phoenix.h"

int	ft_listsize(t_env **env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	if (*env == NULL)
		return (0);
	tmp = *env;
	if (tmp->next == NULL)
	{
		size = 1;
		return (size);
	}
	while (tmp->next != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
