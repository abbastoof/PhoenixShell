/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:44:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/07/03 09:21:02 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_state(t_lexer *state)
{
	if (state->tmp != NULL)
	{
		free(state->tmp);
		state->tmp = NULL;
	}
	if (state->res != NULL)
		state->res = NULL;
	if (state->var != NULL)
	{
		free(state->var);
		state->var = NULL;
	}
	if (state->path != NULL)
		state->path = NULL;
	if (state->des != NULL)
	{
		free(state->des);
		state->des = NULL;
	}
}

void	free_tokens(t_token *tokens)
{
	int	indx;

	indx = 0;
	if (tokens[indx].value)
	{
		while (tokens[indx].value != NULL)
		{
			free(tokens[indx].value);
			tokens[indx].value = NULL;
			indx++;
		}
		free(tokens);
		tokens = NULL;
	}
	return ;
}
