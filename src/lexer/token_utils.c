/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:47:38 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/14 14:37:32 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_token(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL)
		return ;
	while (tokens[i].value != NULL)
	{
		printf("value = %s\n", tokens[i].value);
		printf("type  = %d\n", tokens[i].type);
		i++;
	}
}

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

void	free_tokens(t_token *tokens)
{
	int	indx;

	indx = 0;
	while (tokens[indx].value != NULL)
	{
		free(tokens[indx].value);
		tokens[indx].value = NULL;
		indx++;
	}
	free(tokens);
	tokens = NULL;
	return ;
}
