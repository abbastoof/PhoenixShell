/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/05/26 16:10:37 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char *str, int token_type, t_lexer *state)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (token_type == TOKEN_QUOTE && !state->indquote)
		{
			if (str[i] == '\'' && flag == 0)
				flag = 1;
			else if (str[i] == '\'' && flag == 1)
				flag = 2;
		}
		if (token_type == TOKEN_DQUOTE && !state->inquote)
		{
			if (str[i] == '\"' && flag == 0)
				flag = 1;
			else if (str[i] == '\"' && flag == 1)
				flag = 2;
		}
		if (flag == 2 && (str[i + 1] == ' ' || str[i + 1] == '\0'))
            break ;
		i++;
	}
    if (flag == 2 && str[i + 1] == '\'' || str[i + 1] == '\"')
        handle_strcat(str, state);
}