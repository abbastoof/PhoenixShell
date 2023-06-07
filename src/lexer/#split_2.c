/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:28:01 by atoof             #+#    #+#             */
/*   Updated: 2023/06/07 14:07:38 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirectors(char *str, int i)
{
	if (ft_strncmp(str + i, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str + i, ">>", 2) == 0)
		return (TOKEN_OUTPUT_APPEND);
	else if (ft_strncmp(str + i, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(str + i, "<", 1) == 0)
		return (TOKEN_INPUT);
	else if (ft_strncmp(str + i, ">", 1) == 0)
		return (TOKEN_OUTPUT);
	else
		return (0);
}

int	words_count(char *s)
{
	int		word_count;
	int		i;
	char	quote;
	int		return_res;

	return_res = 0;
	word_count = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		if (redirectors(s, i) != 0)
		{
			return_res = redirectors(s, i);
			if (return_res == TOKEN_OUTPUT_APPEND || return_res == TOKEN_HEREDOC
				|| return_res == TOKEN_EXIT_STATUS)
				i++;
			word_count++;
		}
		if (ft_isquote(s[i]))
		{
			quote = s[i];
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'
						|| redirectors(s, i + 1)))
					break ;
				i++;
			}
			word_count++;
		}
		if (s[i] && !ft_isspace(s[i]) && redirectors(s, i) == 0 && ft_isquote(s[i]) == 0)
		{
			while (s[i] != '\0' && !ft_isspace(s[i]) && redirectors(s, i) == 0)
				i++;
			word_count++;
		}
		if (s[i])
			i++;
	}
	printf("word_count = %d\n", word_count);
	return (word_count);
}

char	**ft_cmdsplit(char *s)
{
	char	**result;
	int		wd_count;
	int		i;
	int		return_res;
	int		start;
	char	quote;

	quote = 0;
	wd_count = 0;
	return_res = 0;
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
		if (s[i] && !ft_isspace(s[i]) && (redirectors(s, i) == 0
				&& !ft_isquote(s[i])))
		{
			start = i;
			while (s[i] != '\0' && !ft_isspace(s[i]) && redirectors(s, i) == 0)
				i++;
			result[wd_count] = ft_substr(s, start, (i - start));
			wd_count++;
		}
		if (s[i] && redirectors(s, i))
		{
			start = i;
			return_res = redirectors(s, i);
			if (return_res == TOKEN_OUTPUT_APPEND || return_res == TOKEN_HEREDOC
				|| return_res == TOKEN_EXIT_STATUS)
			{
				result[wd_count] = ft_substr(s, start, ((i + 2) - start));
				i++;
			}
			result[wd_count] = ft_substr(s, start, ((i + 1) - start));
			wd_count++;
		}
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i];
			start = i;
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && (s[i + 1] == ' ' || s[i + 1] == '\0'
						|| redirectors(s, i + 1)))
					break ;
				i++;
			}
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
			wd_count++;
		}
		if (s[i])
			i++;
	}
	return (result);
}