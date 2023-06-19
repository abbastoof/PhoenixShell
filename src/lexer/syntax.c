/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:52:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/19 18:00:10 by mtoof            ###   ########.fr       */
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

static int	empty_pipe_redirect(int res, char *value)
{
	error_msg(res, value);
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

static void	init_res(t_result *res, t_token *tokens, int i)
{
	res->token_1 = 0;
	res->token_2 = 0;
	res->token_1 = redirectors(tokens[i].value, 0);
	if (tokens[i + 1].value != NULL)
		res->token_2 = redirectors(tokens[i + 1].value, 0);
}

int	syntax(t_token *tokens)
{
	int			i;
	t_result	res;

	i = 0;
	while (tokens[i].value != NULL)
	{
		init_res(&res, tokens, i);
		if (res.token_1 == TOKEN_EXIT_STATUS && tokens[i + 1].value)
			i++;
		if ((redirectors(tokens[i].value, 0) != 0)
			&& (tokens[i + 1].value == NULL))
			return (handle_first_node(redirectors(tokens[i].value, 0)));
		else if (res.token_1 == TOKEN_PIPE && i == 0)
			return (empty_pipe_redirect(res.token_1, NULL));
		else if (res.token_1 == TOKEN_PIPE && (res.token_2 >= 4
				&& res.token_2 <= 7 && tokens[i + 2].value != NULL))
			i++;
		else if (res.token_1 != 0 && res.token_2 != 0
			&& res.token_2 != TOKEN_EXIT_STATUS && tokens[i
				+ 2].value == NULL)
			return (empty_pipe_redirect(res.token_1, tokens[i + 1].value));
		i++;
	}
	return (0);
}
