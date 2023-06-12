/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/06/12 15:40:36 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	join_char(char *str, t_lexer *state, t_env *env, int var_flag)
{
	if (!state->tmp)
	{
		state->tmp = ft_calloc(sizeof(char), 2);
		if (!state->tmp)
			return ;
	}
	dollar_handler(str, state, env, var_flag);
}

int	is_word(char *str, t_lexer *state, t_env *env, int var_flag)
{
	state->flag = 0;
	state->i = 0;
	while (str[state->i])
	{
		handlequote(str, state);
		if ((str[state->i] && state->flag == 0 && str[state->i] != ' ')
			&& (str[state->i] != '\'') && (str[state->i] != '\"'))
		{
			join_char(str, state, env, var_flag);
		}
		else if ((str[state->i] && (state->flag == 1 && str[state->i] != '\''))
			|| (str[state->i] && (state->flag == 2
					&& str[state->i] != '\"')))
			join_char(str, state, env, var_flag);
		else if (state->flag == 0 && str[state->i] == ' ')
			break ;
	}
	// if (validity(state) == -1)
		// free_lexer;
	printf("flag = %d\n", state->flag);
	printf("res = %s\n", state->res);
	state->indx += state->i;
	return (0);
}
