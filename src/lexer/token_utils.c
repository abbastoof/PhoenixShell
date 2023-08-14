/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:47:38 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/15 00:43:29 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tokens(t_token *tokens, int wd_count)
{
	int	index;

	index = 0;
	while (index < wd_count)
	{
		tokens[index].type = 0;
		tokens[index].value = NULL;
		index++;
	}
}

int	dollar_with_character(char *str, t_lexer *state)
{
	if (str[state->i] == '$' && (str[state->i + 1] != '\\' \
	&& (str[state->i + 1] != '%' && str[state->i + 1] != '!' \
	&& str[state->i + 1] != '?')))
		return (1);
	else if (str[state->i] == '$' && str[state->i + 1] == '?')
		return (2);
	else if (str[state->i] == '$' && (str[state->i + 1] == '\\' \
		|| str[state->i + 1] == '%' || str[state->i + 1] == '?'))
		return (3);
	else if (str[state->i] == '$' && (str[state->i + 1] == '!'))
		return (4);
	else
		return (5);
	return (0);
}
