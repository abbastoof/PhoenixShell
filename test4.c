/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:28:01 by atoof             #+#    #+#             */
/*   Updated: 2023/06/04 00:16:26 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int		words_count(const char *s)
{
	int		word_count;
	int		i;
	int		start;
	char	quote;

	word_count = 0;
	i = 0;
	start = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			start = i;
			i++;
			while (s[i] != '\0')
			{
				if (s[i] == quote && s[i + 1] == ' ' || s[i + 1] == '\0')
					break ;
				i++;
			}
			word_count++;
		}
		else if (s[i] != ' ')
		{
			start = i;
			while (s[i] != '\0' && s[i] != ' ')
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
				if (s[i] == quote && s[i + 1] == ' ' || s[i + 1] == '\0')
					break ;
				i++;
			}
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
			wd_count++;
		}
		else if (s[i] != ' ')
		{
			start = i;
			while (s[i] != '\0' && s[i] != ' ')
				i++;
			result[wd_count] = ft_substr(s, start, (i - start) + 1);
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

	// Read input using readline
	printf("Enter a string: ");
	input = readline(NULL);
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
		int i = -1;
		while(result[++i])
		{
			printf("%s\n", result[i]);
		}
		while(i--)
		{
			free(result[i]);
		}
		free(result);
		result = NULL;
	}
	else
	{
		printf("Splitting failed.\n");
	}
	free(input);
	return (0);
}
