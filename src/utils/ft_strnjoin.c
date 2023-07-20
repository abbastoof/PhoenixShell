/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/11/10 08:33:45 by atoof             #+#    #+#             */
/*   Updated: 2022/11/22 17:32:47 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			ft_putstr_fd("Malloc\n", 2);
			return (NULL);
		}
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
