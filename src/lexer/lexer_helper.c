/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/06/01 14:27:35 by mtoof            ###   ########.fr       */
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

void	join_char(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	int		str_indx;

	str_indx = state->i;
	if (!state->tmp)
	{
		state->tmp = ft_calloc(sizeof(char), 2);
		if (!state->tmp)
			return ;
	}
	dollar_handler(str, state, env, var_flag);
}

int	is_word(char *str, t_lexer *state, t_environment *env, int var_flag)
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
			join_char(str, state, env, var_flag);
		else if ((str[state->i] && (state->flag == 1 && str[state->i] != '\''))
			|| (str[state->i] && (state->flag == 2 && str[state->i] != '\"')))
			join_char(str, state, env, var_flag);
		else if (state->flag == 0 && str[state->i] == ' ')
			break ;
	}
	//TODO: ERROR HANDLING
	printf("flag = %d\n", state->flag);
	if (state->flag == 1)
		ft_putstr_fd("The quote is not closed\n", 2);
	else if (state->flag == 2)
		ft_putstr_fd("The double quotes are not closed\n", 2);
	//TODO: ERROR HANDLING
	printf("str tmp = %s\n", (state->tmp));
	state->indx += state->i;
	return (0);
}
