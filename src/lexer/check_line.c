/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:28:00 by atoof             #+#    #+#             */
/*   Updated: 2023/06/08 15:32:13 by mtoof            ###   ########.fr       */
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
		else if (str[c] == '\"' && state->flag == 2)
		{
			state->flag = 0;
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
		else if (str[c] == '\'' && state->flag == 1)
		{
			state->flag = 0;
			state->inquote = 0;
		}
	}
	handledquote(str, state, c);
}

int	check_line(char **line)
{
	t_lexer	state;
	int		c;

	if (line == NULL)
		return (1);
	init_info(&state);
	while (line[state.indx])
	{
		c = 0;
		while (line[state.indx][c])
		{
			handlequote(line[state.indx], &state, c);
			c++;
		}
		state.indx++;
	}
	if (state.inquote == 1 || state.indquote == 1)
		return (-1);
	return (0);
}
