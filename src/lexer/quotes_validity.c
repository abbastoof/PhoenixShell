/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:28:00 by atoof             #+#    #+#             */
/*   Updated: 2023/06/13 11:59:07 by mtoof            ###   ########.fr       */
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

static void	handledquote(char str, t_lexer *state)
{
	if (str == '\"' && !state->inquote)
	{
		if (str == '\"' && state->flag == 0)
		{
			state->flag = 2;
			state->indquote = 1;
		}
		else if (str == '\"' && state->flag == 2)
		{
			state->flag = 0;
			state->indquote = 0;
		}
	}
}

static void	handlequote(char str, t_lexer *state)
{
	if (str == '\'' && !state->indquote)
	{
		if (str == '\'' && state->flag == 0)
		{
			state->flag = 1;
			state->inquote = 1;
		}
		else if (str == '\'' && state->flag == 1)
		{
			state->flag = 0;
			state->inquote = 0;
		}
	}
	handledquote(str, state);
}

int	quotes_validity(char *line)
{
	t_lexer	state;

	if (line == NULL)
		return (1);
	init_info(&state);
	while (line[state.indx] != '\0')
	{
		handlequote(line[state.indx], &state);
		state.indx++;
	}
	if (state.inquote == 1 || state.indquote == 1)
		return (-1);
	return (0);
}
