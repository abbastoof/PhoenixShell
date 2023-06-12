/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:49:03 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/12 16:12:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_quotes(t_token *tokens, t_env *env, t_lexer *state)
{
	int	token_indx;
	int	value_indx;

	token_indx = 0;
	while (tokens[token_indx].value)
	{
		value_indx = 0;
		while (tokens[token_indx].value[value_indx])
		{
			if (tokens[token_indx].value[value_indx] == '\'')
			{
				is_word(tokens[token_indx].value, &state, env, 0);
				break ;
			}
			else if ((tokens[token_indx].value[value_indx] == '\"')
				|| (tokens[token_indx].value[value_indx] == '$'))
			{
				is_word(tokens[token_indx].value, &state, env, 1);
				break ;
			}
			value_indx++;
		}
		token_indx++;
	}
}
