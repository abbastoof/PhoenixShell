/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:44:00 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/20 01:44:00 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*error_handling(void)
{
	ft_putstr_fd("Malloc\n", 2);
	return (NULL);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*sjoin;

	if (s1 && s2)
	{
		if (n > ft_strlen(s2))
			n = ft_strlen(s2);
		sjoin = (char *)malloc(sizeof(char) * (ft_strlen(s1) + n + 1));
		if (!sjoin)
			return (error_handling());
		i = -1;
		while (s1[++i])
			sjoin[i] = s1[i];
		j = -1;
		while (++j < n)
		{
			sjoin[i] = s2[j];
			i++;
		}
		sjoin[i] = '\0';
		return (sjoin);
	}
	return (NULL);
}
