/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:11:17 by atoof             #+#    #+#             */
/*   Updated: 2023/06/15 11:36:38 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(int res, char *msg)
{
	if (res != TOKEN_EXIT_STATUS)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (res >= 4 && res <= 7)
			ft_putstr_fd("newline", 2);
		else if (res == 3)
			ft_putstr_fd("|", 2);
		else if (msg != NULL)
			ft_putstr_fd(msg, 2);
		ft_putstr_fd("'\n", 2);
	}
}

int	syntax(t_token *tokens)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (tokens[i].value && (tokens[i + 1].value == NULL))
	{
		res = redirectors(tokens[i].value, 0);
		if (!res || res == TOKEN_EXIT_STATUS)
			return (0);
		error_msg(res, NULL);
		return (1);
	}
	while (tokens[i].value && tokens[i + 1].value != NULL)
	{
		if (redirectors(tokens[i].value, 0) == TOKEN_PIPE && i == 0)
		{
			error_msg(0, tokens[i].value);
			return (1);
		}
		else if ((redirectors(tokens[i].value, 0) != 0)
			&& (redirectors(tokens[i + 1].value, 0) != 0))
		{
			error_msg(0, tokens[i + 1].value);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_incorrect_quotes(t_token *tokens)
{
	int	indx;

	indx = 0;
	if (tokens == NULL)
		return (1);
	while (tokens[indx].value != NULL)
	{
		if (quotes_validity(tokens[indx].value) == -1)
		{
			ft_putstr_fd("open quotes\n", 2);
			{
				free_tokens(tokens);
				return (1);
			}
		}
		indx++;
	}
	if (syntax(tokens) == 1)
	{
		free_tokens(tokens);
		return (1);
	}
	return (0);
}
