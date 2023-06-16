/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:52:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/16 17:44:37 by mtoof            ###   ########.fr       */
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

static int	empty_pipe(char *value)
{
	error_msg(0, value);
	return (1);
}

static int	handle_first_node(int res)
{
	if (!res || res == TOKEN_EXIT_STATUS)
		return (0);
	else
	{
		error_msg(res, NULL);
		return (1);
	}
}

int	syntax(t_token *tokens)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (tokens[i].value != NULL)
	{
		res = redirectors(tokens[i].value, 0);
		if (tokens[i].value && (tokens[i + 1].value == NULL))
			return (handle_first_node(res));
		else if (res == TOKEN_PIPE && i == 0)
			return (empty_pipe(tokens[i].value));
		else if (res == TOKEN_PIPE && (redirectors(tokens[i
						+ 1].value, 0) >= 4 && redirectors(tokens[i
						+ 1].value, 0) <= 7) && tokens[i + 2].value != NULL)
			i++;
		else if (res != 0 && redirectors(tokens[i
					+ 1].value, 0) != 0 && tokens[i + 2].value == NULL)
		{
			error_msg(0, tokens[i + 1].value);
			return (1);
		}
		i++;
	}
	return (0);
}
