/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:28:00 by atoof             #+#    #+#             */
/*   Updated: 2023/06/06 22:25:49 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_lexer *s)
{
	s->inquote = 0;
	s->indquote = 0;
	s->indx = 0;
	s->flag = 0;
}

static void	handledquote(char *str, t_lexer *s)
{
	if (str[s->i] == '\"' && !s->inquote)
	{
		if (str[s->i] == '\"' && s->flag == 0)
		{
			s->flag = 2;
			s->i++;
			s->indquote = 1;
		}
		if (str[s->i] == '\"' && s->flag == 2)
		{
			s->flag = 0;
			s->indquote = 0;
		}
		printf("flag = %d\n", s->flag);
	}
}

static void	handlequote(char *str, t_lexer *s)
{
	if (str[s->i] == '\'' && !s->indquote)
	{
		if (str[s->i] == '\'' && s->flag == 0)
		{
			s->flag = 1;
			s->i++;
			s->inquote = 1;
		}
		if (str[s->i] == '\'' && s->flag == 1)
		{
			s->flag = 0;
			s->inquote = 0;
		}
	}
	handledquote(str, s);
}

int	check_line(char **line)
{
	t_lexer	s;

	init_info(&s);
	while (line[s.indx] != NULL)
	{
		s.i = 0;
		while (line[s.indx][s.i])
		{
			handlequote(line[s.indx], &s);
			s.i++;
		}
		s.indx++;
	}
	if (s.inquote == 1)
	{
		ft_putstr_fd("The quote is not closed\n", 2);
		return (-1);
	}
	else if (s.indquote == 1)
	{
		ft_putstr_fd("The double quotes are not closed\n", 2);
		return (-1);
	}
	return (0);
}
