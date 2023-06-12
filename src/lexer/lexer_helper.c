/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/06/12 16:58:23 by mtoof            ###   ########.fr       */
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

int	expand_var(t_token *token, t_lexer *state, t_env *env, int var_flag)
{
	state->flag = 0;
	state->i = 0;
	while (token->value[state->i])
	{
		handlequote(token->value, state);
		if ((token->value[state->i] && state->flag == 0
				&& token->value[state->i] != ' ')
			&& (token->value[state->i] != '\'')
			&& (token->value[state->i] != '\"'))
			join_char(token->value, state, env, var_flag);
		else if ((token->value[state->i] && (state->flag == 1
					&& token->value[state->i] != '\''))
			|| (token->value[state->i] && (state->flag == 2
					&& token->value[state->i] != '\"')))
			join_char(token->value, state, env, var_flag);
		else if (state->flag == 0 && token->value[state->i] == ' ')
			break ;
	}
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	token->value = ft_strdup(state->res);
	return (0);
}
