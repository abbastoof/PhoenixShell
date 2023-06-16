/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:52:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/16 20:39:43 by atoof            ###   ########.fr       */
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

int	syntax(t_token *tokens)
{
	int	i;
	int	res_tok_1;
	int	res_tok_2;

	res_tok_1 = 0;
	res_tok_2 = 0;
	i = 0;
	while (tokens[i].value != NULL)
	{
		res_tok_1 = redirectors(tokens[i].value, 0);
		res_tok_2 = redirectors(tokens[i + 1].value, 0);
		if (res_tok_1 == TOKEN_EXIT_STATUS && tokens[i + 1].value)
			i++;
		if ((redirectors(tokens[i].value, 0) != 0)
			&& (tokens[i + 1].value == NULL))
			return (handle_first_node(redirectors(tokens[i].value, 0)));
		else if (res_tok_1 == TOKEN_PIPE && i == 0)
			return (empty_pipe_redirect(res_tok_1, NULL));
		else if (res_tok_1 == TOKEN_PIPE && (res_tok_2 >= 4 && res_tok_2 <= 7
				&& tokens[i + 2].value != NULL))
			i++;
		else if (res_tok_1 != 0 && res_tok_2 != 0
			&& res_tok_2 != TOKEN_EXIT_STATUS && tokens[i + 2].value == NULL)
			return (empty_pipe_redirect(res_tok_1, tokens[i + 1].value));
		i++;
	}
	return (0);
}
