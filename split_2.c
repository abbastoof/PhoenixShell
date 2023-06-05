/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:28:01 by atoof             #+#    #+#             */
/*   Updated: 2023/06/05 22:00:11 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TOKEN_CMD 1
#define TOKEN_ARG 2
#define TOKEN_PIPE 3
#define TOKEN_INPUT 4
#define TOKEN_OUTPUT 5
#define TOKEN_OUTPUT_APPEND 6
#define TOKEN_HEREDOC 7
#define TOKEN_VARIABLE 8
#define TOKEN_EXIT_STATUS 9
#define TOKEN_QUOTE 10
#define TOKEN_DQUOTE 11

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (i < n && ss1[i] != '\0' && ss2[i] != '\0')
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i != n)
		return (ss1[i] - ss2[i]);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	*ft_memcpy(void *to, const void *from, unsigned int size)
{
	unsigned int	i;
	char			*from_cpy;
	char			*to_cpy;

	from_cpy = (char *)from;
	to_cpy = (char *)to;
	i = 0;
	if (!to && !from)
		return ((void *)0);
	while (i < size)
	{
		to_cpy[i] = from_cpy[i];
		i++;
	}
	return (to_cpy);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = c;
	return (s);
}

void	ft_bzero(void *s, size_t len)
{
	ft_memset((void *)s, 0, len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	size_t	mult;

	mult = count * size;
	if (count > 0 && size > 0)
	{
		if (mult % count != 0 || mult % size != 0)
			return (NULL);
	}
	pointer = malloc(mult);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, mult);
	return (pointer);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_length;
	char			*sub;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
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
			return (NULL);
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

static int	redirectors(char *str, int	i)
{
	// printf("str[i] = %c\n", str[i]);
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
	else if (str[i] == '$')
	{
		if (ft_strncmp(str + i, "$?", 2) == 0)
			return (TOKEN_EXIT_STATUS);
		else
			return (TOKEN_VARIABLE);
	}
	else
		return (0);
}

int	words_count(char *s)
{
	int		word_count;
	int		i;
	char	quote;
	int		return_res = 0;
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
		if (!ft_isspace(s[i]) && redirectors(s, i) == 0)
		{
			while (s[i] != '\0' && !ft_isspace(s[i]) && redirectors(s, i) == 0)
				i++;
			word_count++;
		}
		if (redirectors(s, i) != 0)
		{
			return_res = redirectors(s, i);
			if (return_res == TOKEN_OUTPUT_APPEND || return_res == TOKEN_HEREDOC
				|| return_res == TOKEN_EXIT_STATUS)
				i++;
			else if (return_res == TOKEN_VARIABLE)
			{
				while (s[i] != '\0' && !ft_isspace(s[i]))
					i++;
			}
			word_count++;
		}
		i++;
	}
	return (word_count);
}

char	**ft_cmdsplit(char *s)
{
	char	**result;
	int		wd_count;
	int		i;
	int		return_res = 0;
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
		if (s[i] && !ft_isspace(s[i]) && (redirectors(s, i) == 0 && !ft_isquote(s[i])))
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
				// printf("got here\n");
				result[wd_count] = ft_substr(s, start, ((i + 2) - start));
				i++;
			}	
			else if (return_res == TOKEN_VARIABLE)
			{
				while (s[i] != '\0' && !ft_isspace(s[i]))
					i++;
				result[wd_count] = ft_substr(s, start, (i - start));
			}
			else
				result[wd_count] = ft_substr(s, start, ((i + 1) - start));
			wd_count++;
		}
		if (s[i] && s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			start = i;
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && (s[i + 1] == ' ' || s[i + 1] == '\0' || redirectors(s, i + 1) != 0))
					break ;
				i++;
			}
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
			// printf("result[wd_count] = %s", ft_substr(s, start, (i - start) + 1));
			wd_count++;
		}
		i++;
	}

	return (result);
}

int	main(void)
{
	char	*input;
	char	**result;
	int		i;

	// Read input using readline
	// printf("Enter a string: ");
	input = readline("Enter a string: ");
	if (!input)
	{
		printf("Error reading input.\n");
		return (1);
	}
	result = ft_cmdsplit(input);
	// Print the result
	printf("Result:\n");
	if (result)
	{
		i = -1;
		while (result[++i])
		{
			printf("%s\n", result[i]);
		}
	}
	// 	while (i--)
	// 	{
	// 		free(result[i]);
	// 	}
	// 	free(result);
	// 	result = NULL;
	// }
	// else
	// {
	// 	printf("Splitting failed.\n");
	// }
	free(input);
	return (0);
}