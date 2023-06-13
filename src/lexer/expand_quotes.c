/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:49:03 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/13 16:34:27 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_quotes(t_token *tokens, t_env *env, t_lexer *state)
{
	int	value_indx;

	while (tokens[state->token_indx].value)
	{
		value_indx = 0;
		while (tokens[state->token_indx].value[value_indx])
		{
			if (tokens[state->token_indx].value[value_indx] == '\'')
			{
				expand_var(&tokens[state->token_indx], state, env, 0);
				break ;
			}
			else if ((tokens[state->token_indx].value[value_indx] == '\"')
				|| (tokens[state->token_indx].value[value_indx] == '$'))
			{
				expand_var(&tokens[state->token_indx], state, env, 1);
				break ;
			}
			value_indx++;
		}
		state->token_indx++;
	}
}
