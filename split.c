/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:28:01 by atoof             #+#    #+#             */
/*   Updated: 2023/06/04 23:26:01 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	words_count(const char *s)
{
	int		word_count;
	int		i;
	char	quote;

	word_count = 0;
	i = 0;

	while (s[i] != '\0')
	{
		if (ft_isquote(s[i]))
		{
			quote = s[i];
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
					break ;
				i++;
			}
			word_count++;
		}
		else if (!ft_isspace(s[i]))
		{
			while (s[i] != '\0' && !ft_isspace(s[i]))
				i++;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

char	**ft_cmdsplit(char const *s)
{
	char	**result;
	int		wd_count;
	int		i;
	int		start;
	char	quote;

	i = 0;
	start = 0;
	result = NULL;
	wd_count = words_count(s);
	printf("wd count = %d\n", wd_count);
	result = ft_calloc((wd_count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	wd_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			start = i;
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && (s[i + 1] == ' ' || s[i + 1] == '\0'))
					break ;
				i++;
			}
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
			wd_count++;
		}
		else if (!ft_isspace(s[i]))
		{
			start = i;
			while (s[i] != '\0' && !ft_isspace(s[i]))
				i++;
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
			wd_count++;
		}
		i++;
	}
	return (result);
}

