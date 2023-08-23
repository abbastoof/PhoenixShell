/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:34 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 10:59:54 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_in_out_pipe(char *str, t_cmdsplit *cmd, t_token *new)
{
	new->value = ft_substr(str, cmd->start, ((cmd->index + 1) \
				- cmd->start));
	if (!new->value)
		return (-1);
	new->type = cmd->res;
	return (0);
}

static int	handle_redirector(char *str, t_cmdsplit *cmd, t_token **tokens)
{
	t_token	*new;

	new = new_token();
	cmd->start = cmd->index;
	cmd->res = redirectors(str, cmd->index);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
	{
		new->value = ft_substr(str, cmd->start, ((cmd->index + 2) \
				- cmd->start));
		if (!new->value)
			return (-1);
		new->type = cmd->res;
		cmd->index++;
	}
	else
	{
		if (handle_in_out_pipe(str, cmd, new) == -1)
			return (-1);
	}
	if (ft_token_add_back(tokens, new) == -1)
		return (-1);
	return (0);
}

static int	handle_word(char *str, t_cmdsplit *cmd, t_token **tokens)
{
	t_token	*new;

	new = new_token();
	if (!new)
		return (-1);
	new->type = 0;
	cmd->start = cmd->index;
	while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
		&& redirectors(str, cmd->index) == 0)
	{
		if (ft_isquote(str[cmd->index]))
			word_contain_quote_2(str, cmd);
		cmd->index++;
	}
	new->value = ft_substr(str, cmd->start, (cmd->index - cmd->start));
	if (!new->value)
		return (-1);
	if (ft_token_add_back(tokens, new) == -1)
		return (-1);
	return (0);
}

static int	init_result(char *str, t_cmdsplit *cmd, t_token **tokens)
{
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] && !ft_isspace(str[cmd->index]) && (redirectors(str,
					cmd->index) == 0 && !ft_isquote(str[cmd->index])))
		{
			if (handle_word(str, cmd, tokens) == -1)
				return (-1);
		}
		if (str[cmd->index] && redirectors(str, cmd->index))
		{
			if (handle_redirector(str, cmd, tokens))
				return (-1);
		}
		if (str[cmd->index] && (ft_isquote(str[cmd->index])))
		{
			if (split_quote(str, cmd, tokens) == -1)
				return (-1);
		}
		if (str[cmd->index] != '\0')
			cmd->index++;
	}
	return (0);
}

int	ft_cmdtrim(char *str, t_token **tokens)
{
	t_cmdsplit	cmd;

	init_cmdsplit(&cmd);
	cmd.wd_count = 0;
	cmd.index = 0;
	if (init_result(str, &cmd, tokens) == -1)
	{
		ft_putstr_fd("Malloc split_line\n", 2);
		free_tokens(tokens);
		return (-1);
	}
	return (0);
}
