/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/06/13 16:09:31 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handledquote(char *str, t_lexer *state)
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

static void	handlequote(char *str, t_lexer *state)
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

static void	join_char(char *str, t_lexer *state, t_env *env, int var_flag)
{
	if (!state->tmp)
	{
		state->tmp = ft_calloc(sizeof(char), 2);
		if (!state->tmp)
			return ;
	}
	dollar_handler(str, state, env, var_flag);
}

static void	replace_value(t_token *token, t_lexer *state)
{
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	if (state->res)
		token->value = ft_strdup(state->res);
	else
		token->value = NULL;
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
	replace_value(token, state);
	free_state(state);
	return (0);
}
