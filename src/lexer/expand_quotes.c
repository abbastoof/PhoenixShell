/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:49:03 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/24 14:30:31 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_value(t_token *token, t_lexer *state)
{
	if (state->res != NULL)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		token->value = ft_strdup(state->res);
		if (!token->value)
		{
			ft_putstr_fd("Malloc expand_var\n", 2);
			return (-1);
		}
	}
	else
	{
		if (token->value)
			free(token->value);
		token->value = NULL;
	}
	free_state(state);
	return (0);
}

int	need_expantion(t_token *token, t_lexer *state, t_env **env, int expand_flag)
{
	if ((token->value[state->i] && state->flag == 0 \
	&& token->value[state->i] != ' ') \
	&& (token->value[state->i] != '\'') && (token->value[state->i] != '\"'))
	{
		if (join_char(token->value, state, env, expand_flag) == -1)
			return (-1);
	}
	else if ((token->value[state->i] && (state->flag == 1 \
	&& token->value[state->i] != '\'')) || (token->value[state->i] \
	&& (state->flag == 2 && token->value[state->i] != '\"')))
	{
		if (join_char(token->value, state, env, expand_flag) == -1)
			return (-1);
	}
	else if (state->flag == 0 && token->value[state->i] == ' ')
		return (-2);
	return (0);
}

int	expand_var(t_token *token, t_lexer *state, t_env **env, int expand_flag)
{
	int	result;

	result = 0;
	state->flag = 0;
	state->i = 0;
	while (token->value[state->i])
	{
		checkquote(token->value, state);
		if ((token->value[state->i] != '\0' && state->indquote == 1 && \
		expand_flag == 0) || (token->value[state->i] != '\0' \
		&& state->indquote == 0 && state->inquote == 0 && \
		expand_flag == 0 && token->value[state->i] == '$'))
			expand_flag = 1;
		result = need_expantion(token, state, env, expand_flag);
		if (result == -1)
			return (-1);
		else if (result == -2)
			break ;
	}
	if (token->value[state->i] != '\0')
		return (0);
	replace_value(token, state);
	return (0);
}

void	expand_quotes(t_token **tokens, t_env **env, t_lexer *state)
{
	int		value_indx;
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		value_indx = 0;
		while (tmp->value[value_indx])
		{
			if (tmp->value[value_indx] == '\'')
			{
				expand_var(tmp, state, env, 0);
				break ;
			}
			else if ((tmp->value[value_indx] == '\"') \
			|| (tmp->value[value_indx] == '$'))
			{
				expand_var(tmp, state, env, 1);
				break ;
			}
			value_indx++;
		}
		tmp = tmp->next;
	}
}

int	expansion(t_token **tokens, t_lexer *state, t_env **env)
{
	int	flag;

	flag = 0;
	if (tokens_list_size(tokens) == 1 && (*tokens)->value != NULL \
	&& (*tokens)->value[0] == '$')
		flag = 1;
	expand_quotes(tokens, env, state);
	if (flag == 1 && (*tokens)->value == NULL)
	{
		free_tokens(tokens);
		tokens = NULL;
		g_exit_status = 0;
		return (1);
	}
	return (0);
}
