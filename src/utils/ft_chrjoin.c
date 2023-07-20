/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:57:35 by atoof             #+#    #+#             */
/*   Updated: 2023/07/20 13:05:48 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chrjoin(char const *s1, char const s2)
{
	size_t	len1;
	size_t	i;
	char	*sjoin;

	if (s1)
	{
		len1 = ft_strlen(s1);
		sjoin = (char *)malloc(sizeof(char) * (len1 + 2));
		if (!sjoin)
		{
			ft_putstr_fd("Malloc\n", 2);
			return (NULL);
		}
		i = -1;
		while (s1[++i])
			sjoin[i] = s1[i];
		sjoin[len1] = s2;
		len1++;
		sjoin[len1] = '\0';
		return (sjoin);
	}
	return (NULL);
}
