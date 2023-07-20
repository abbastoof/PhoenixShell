/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:33:21 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 13:08:04 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **ptr, size_t size)
{
	size_t		index;
	char		**new;

	index = 0;
	while (ptr[index])
		index++;
	if (size <= index)
		return (ptr);
	new = ft_calloc(sizeof(char *), size);
	if (!new)
	{
		ft_putstr_fd("Malloc\n", 2);
		return (ptr);
	}
	index = 0;
	while (ptr[index])
	{
		new[index] = ft_strdup(ptr[index]);
		{
			ft_putstr_fd("Malloc\n", 2);
			return (NULL);
		}
		index++;
	}
	return (new);
}
