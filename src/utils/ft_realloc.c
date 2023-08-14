/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:33:21 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 13:11:32 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_ptrlen(char **ptr)
{
	size_t	index;

	index = 0;
	while (ptr[index])
		index++;
	return (index);
}

char	**ft_realloc(char **ptr, size_t size)
{
	size_t	index;
	char	**new;

	index = ft_ptrlen(ptr);
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
		if (!new[index])
		{
			ft_putstr_fd("Malloc\n", 2);
			return (NULL);
		}
		index++;
	}
	return (new);
}
