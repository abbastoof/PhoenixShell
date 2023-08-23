/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:44:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 16:23:32 by mtoof            ###   ########.fr       */
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

void	free_tokens(t_token **tokens)
{
	t_token	*list;

	while ((*tokens))
	{
		list = (*tokens)->next;
		if ((*tokens)->value)
		{
			free((*tokens)->value);
			(*tokens)->value = NULL;
		}
		free((*tokens));
		(*tokens) = list;
	}
	return ;
}
