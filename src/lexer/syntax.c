/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:52:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/22 16:45:35 by mtoof            ###   ########.fr       */
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
		g_exit_status = 1;
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

static void	init_res(t_result *res, t_token *tokens)
{
	res->token_1 = 0;
	res->token_2 = 0;
	res->token_1 = redirectors(tokens->value, 0);
	if (tokens->next != NULL && tokens->next->value != NULL)
		res->token_2 = redirectors(tokens->next->value, 0);
}

int	syntax(t_token **tokens)
{
	t_token		*tmp;
	t_result	res;

	tmp = *tokens;
	if (tmp->type == TOKEN_PIPE)
		return (empty_pipe_redirect(res.token_1, NULL));
	while (tmp != NULL)
	{
		init_res(&res, tmp);
		if (check_consecutive_redirs(res, tmp) == 1)
			tmp = tmp->next;
		if (check_consecutive_redirs(res, tmp) == 2)
			return (handle_first_node(redirectors(tmp->value, 0)));
		else if (check_consecutive_redirs(res, tmp) == 3)
			tmp = tmp->next;
		else if (check_consecutive_redirs(res, tmp) == 4)
			return (empty_pipe_redirect(res.token_1, tmp->next->value));
		else if (check_consecutive_redirs(res, tmp) == 5)
			return (empty_pipe_redirect(res.token_1, tmp->next->value));
		else if (check_consecutive_redirs(res, tmp) == 6)
			return (empty_pipe_redirect(0, tmp->next->value));
		tmp = tmp->next;
	}
	return (0);
}
