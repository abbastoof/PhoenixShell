/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:56:06 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/29 15:10:18 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

typedef struct s_lexer
{
	int		indx;
	char	*crnt_str;
	char	*start;
	int		inquote;
	int		indquote;
	int		token_indx;
	char	*str_cat;
}			t_lexer;

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
		sjoin [len1] = '\0';
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

int	is_word(char *str, t_lexer *state)
{
	int		i;
	int		flag;
	char	*tmp;
	char	*res;

	flag = 0;
	i = 0;
	tmp = calloc(1, 1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' && !state->indquote)
		{
			if (str[i] == '\'' && flag == 0)
			{
				flag = 1;
				i++;
				state->inquote = 1;
			}
			if (str[i] == '\'' && flag == 1)
			{
				flag = 0;
				i++;
				state->inquote = 0;
			}
		}
		else if (str[i] == '\"' && !state->inquote)
		{
			if (str[i] == '\"' && flag == 0)
			{
				flag = 2;
				i++;
				state->indquote = 1;
			}
			if (str[i] == '\"' && flag == 2)
			{
				flag = 0;
				i++;
				state->indquote = 0;
			}
		}
		if (str[i] && !flag && str[i] != ' ' && ((str[i] != '\'') && (str[i] != '\"')))
		{
			printf("flag = %d, str[i] = %c\n",flag, str[i]);
			res = ft_strjoin(tmp, str[i]);
			free(tmp);
			tmp = res;
		}
		else if ((str[i] && (flag == 1 && str[i] != '\'')) || (str[i] && (flag == 2 && str[i] != '\"')))
		{
			printf("flag = %d, str[i] = %c\n",flag, str[i]);
			res = ft_strjoin(tmp, str[i]);
			free(tmp);
			tmp = res;
		}
		else if (flag == 0 && str[i] == ' ')
			break ;
		i++;
	}
	printf("flg = %d\n", flag);
	if (flag == 1)
		ft_putstr_fd("The quote is not closed\n", 2);
	else if (flag == 2)
		ft_putstr_fd("The double quotes are not closed\n", 2);
	return (0);
}

static void	init_info(t_lexer *state)
{
	state->inquote = 0;
	state->indquote = 0;
}

int main()
{
	char	*cmd;
	t_lexer	state;

	init_info(&state);
	while (1)
	{
		cmd = readline("my shell$>");
		is_word(cmd, &state);
		if (cmd)
			free(cmd);
	}
	return (0);
}
