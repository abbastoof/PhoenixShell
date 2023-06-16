/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:11:17 by atoof             #+#    #+#             */
/*   Updated: 2023/06/16 17:08:53 by mtoof            ###   ########.fr       */
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

static int	quotes_validity(char *line)
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

int	check_incorrect_quotes(t_token *tokens)
{
	int	indx;

	indx = 0;
	if (tokens == NULL)
		return (1);
	while (tokens[indx].value != NULL)
	{
		if (quotes_validity(tokens[indx].value) == -1)
		{
			ft_putstr_fd("open quotes\n", 2);
			{
				free_tokens(tokens);
				return (1);
			}
		}
		indx++;
	}
	if (syntax(tokens) == 1)
	{
		free_tokens(tokens);
		return (1);
	}
	return (0);
}
