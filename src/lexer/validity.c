/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:44:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/02 10:23:38 by mtoof            ###   ########.fr       */
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

int	validity(t_lexer *state)
{
	if (state->flag == 1)
	{
		ft_putstr_fd("The quote is not closed\n", 2);
		free_state(state);
		return (-1);
	}
	else if (state->flag == 2)
	{
		ft_putstr_fd("The double quotes are not closed\n", 2);
		free_state(state);
		return (-1);
	}
	return (0);
}
