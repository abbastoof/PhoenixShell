/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:28:00 by atoof             #+#    #+#             */
/*   Updated: 2023/06/06 15:24:25 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_lexer *state)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->flag = 0;
}

static void	handledquote(char *str, t_lexer *state, int c)
{
	if (str[c] == '\"' && !state->inquote)
	{
		if (str[c] == '\"' && state->flag == 0)
		{
			state->flag = 2;
			c++;
			state->indquote = 1;
		}
		if (str[c] == '\"' && state->flag == 2)
		{
			state->flag = 0;
			c++;
			state->indquote = 0;
		}
	}
}

static void	handlequote(char *str, t_lexer *state, int c)
{
	if (str[c] == '\'' && !state->indquote)
	{
		if (str[c] == '\'' && state->flag == 0)
		{
			state->flag = 1;
			c++;
			state->inquote = 1;
		}
		if (str[c] == '\'' && state->flag == 1)
		{
			state->flag = 0;
			c++;
			state->inquote = 0;
		}
	}
	handledquote(str, state, c);
}

int	check_line(char **line)
{
	t_lexer	state;
	int		c;

	c = 0;
	init_info(&state);
	while (line[state.indx])
	{
		while (line[state.indx][c])
		{
			handlequote(line[state.indx], &state, c);
			c++;
		}
		state.indx++;
	}
	if (state.flag == 1)
	{
		ft_putstr_fd("The quote is not closed\n", 2);
		return (-1);
	}
	else if (state.flag == 2)
	{
		ft_putstr_fd("The double quotes are not closed\n", 2);
		return (-1);
	}
	return (0);
}
