/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:47:38 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/09 18:09:00 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value != NULL)
	{
		printf("value = %s\n", tokens[i].value);
		printf("type  = %d\n", tokens[i].type);
		i++;
	}
}

void	check_incorrect_quotes(t_token *tokens)
{
	int	indx;

	indx = 0;
	if (tokens == NULL)
		return ;
	while (tokens[indx].value != NULL)
	{
		if (check_line(tokens[indx].value) == -1)
		{
			ft_putstr_fd("open quotes\n", 2);
			{
				free_tokens(tokens);
				return ;
			}
		}
		indx++;
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
