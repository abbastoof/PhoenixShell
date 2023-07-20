/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:58:25 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/20 18:54:07 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shelvl_value(char *value)
{
	int	res;

	res = 0;
	if (value != NULL)
	{
		res = ft_atoi(value);
		res++;
		return (ft_itoa(res));
	}
	return (NULL);
}

