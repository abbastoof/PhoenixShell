/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:56:06 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/30 17:33:40 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_lexer
{
	int		indx;
	char	*crnt_str;
	char	*start;
	int		inquote;
	int		indquote;
	int		token_indx;
	char	*str_cat;
	int		flag;
	int		i;
	char	*tmp;
	char	*res;
}			t_lexer;

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_lng;
	size_t	src_lng;
	size_t	i;

	src_lng = ft_strlen(src);
	dest_lng = 0;
	if (dst)
		dest_lng = ft_strlen(dst);
	i = dest_lng;
	if (!src || !*src)
		return (dest_lng);
	else if (dstsize <= dest_lng)
		return (dstsize + src_lng);
	while (*src && dstsize > dest_lng && i != dstsize - 1)
		*(dst + i++) = *src++;
	*(dst + i) = '\0';
	return (dest_lng + src_lng);
}

char	*ft_strjoin(char const *s1, char const s2)
{
	size_t	len1;
	size_t	i;
	char	*sjoin;

	if (s1)
	{
		len1 = ft_strlen(s1);
		sjoin = (char *)malloc(sizeof(char) * (len1 + 2));
		if (!sjoin)
			return (NULL);
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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

void	handledquote(char *str, t_lexer *state)
{
	if (str[state->i] == '\"' && !state->inquote)
	{
		if (str[state->i] == '\"' && state->flag == 0)
		{
			state->flag = 2;
			state->i++;
			state->indquote = 1;
		}
		if (str[state->i] == '\"' && state->flag == 2)
		{
			state->flag = 0;
			state->i++;
			state->indquote = 0;
		}
	}
}

void	handlequote(char *str, t_lexer *state)
{
	if (str[state->i] == '\'' && !state->indquote)
	{
		if (str[state->i] == '\'' && state->flag == 0)
		{
			state->flag = 1;
			state->i++;
			state->inquote = 1;
		}
		if (str[state->i] == '\'' && state->flag == 1)
		{
			state->flag = 0;
			state->i++;
			state->inquote = 0;
		}
	}
	handledquote(str, state);
}

void	join_char(char *str, t_lexer *state)
{
	printf("state->flag = %d, str[state->i] = %c\n", state->flag,
			str[state->i]);
	if (state->tmp == NULL)
	{
		state->tmp = malloc(sizeof(char) * 2);
		if (!state->tmp)
			return ;
	}
	state->res = ft_strjoin(state->tmp, str[state->i]);
	if (state->tmp)
		free(state->tmp);
	state->tmp = state->res;
	state->i++;
}

int	is_word(char *str, t_lexer *state)
{
	state->flag = 0;
	state->i = 0;
	while (str[state->i] == ' ' || str[state->i] == '\t')
		state->i++;
	while (str[state->i])
	{
		handlequote(str, state);
		if ((str[state->i] && state->flag == 0 && str[state->i] != ' ')
			&& (str[state->i] != '\'') && (str[state->i] != '\"'))
			join_char(str, state);
		else if ((str[state->i] && (state->flag == 1 && str[state->i] != '\''))
			|| (str[state->i] && (state->flag == 2
					&& str[state->i] != '\"')))
			join_char(str, state);
		else if (state->flag == 0 && str[state->i] == ' ')
			break ;
	}
	if (state->flag == 1)
		ft_putstr_fd("The quote is not closed\n", 2);
	else if (state->flag == 2)
		ft_putstr_fd("The double quotes are not closed\n", 2);
	printf("cmd = %s\n", state->tmp);
	return (0);
}

static void	init_info(t_lexer *state)
{
	state->inquote = 0;
	state->indquote = 0;
}

void	ft_free(t_lexer *state)
{
	printf("going for free\n");
	if (state->tmp)
		free(state->tmp);
	state->tmp = NULL;
}

int	main(void)
{
	char	*cmd;
	t_lexer	state;

	init_info(&state);
	while (1)
	{
		cmd = readline("my shell$>");
		add_history(cmd);
		is_word(cmd, &state);
		if (cmd != '\0')
			free(cmd);
		if (state.tmp != NULL)
		{
			// printf("tmp = %p\n", state.tmp);
			ft_free(&state);
		}
	}
	return (0);
}
