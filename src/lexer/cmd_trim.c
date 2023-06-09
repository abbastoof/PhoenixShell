/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:34 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/08 18:53:39 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote(char *str, t_cmdsplit *cmd, t_token *tokens)
{
	cmd->quote = str[cmd->index];
	cmd->start = cmd->index;
	cmd->index++;
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] == cmd->quote && (ft_isspace(str[cmd->index + 1])
				|| str[cmd->index + 1] == '\0' || redirectors(str, cmd->index
					+ 1)))
			break ;
		cmd->index++;
	}
	tokens[cmd->wd_count].value = ft_substr(str, cmd->start, (cmd->index
				- cmd->start) + 1);
}

static void	handle_redirector(char *str, t_cmdsplit *cmd, t_token *tokens)
{
	cmd->start = cmd->index;
	cmd->res = redirectors(str, cmd->index);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
	{
		tokens[cmd->wd_count].value = ft_substr(str, cmd->start, ((cmd->index
						+ 2) - cmd->start));
		tokens[cmd->wd_count].type = cmd->res;
		cmd->index++;
	}
	else
	{
		tokens[cmd->wd_count].value = ft_substr(str, cmd->start, ((cmd->index
						+ 1) - cmd->start));
		tokens[cmd->wd_count].type = cmd->res;
	}
}

static void	handle_word(char *str, t_cmdsplit *cmd, t_token *tokens)
{
	cmd->start = cmd->index;
	while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
		&& redirectors(str, cmd->index) == 0)
		cmd->index++;
	tokens[cmd->wd_count].value = ft_substr(str, cmd->start, (cmd->index
				- cmd->start));
}

static void	init_result(char *str, t_cmdsplit *cmd, t_token *tokens)
{
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] && !ft_isspace(str[cmd->index]) && (redirectors(str,
					cmd->index) == 0 && !ft_isquote(str[cmd->index])))
		{
			handle_word(str, cmd, tokens);
			cmd->wd_count++;
		}
		if (str[cmd->index] && redirectors(str, cmd->index))
		{
			handle_redirector(str, cmd, tokens);
			cmd->wd_count++;
		}
		if (str[cmd->index] && (ft_isquote(str[cmd->index])))
		{
			handle_quote(str, cmd, tokens);
			cmd->wd_count++;
		}
		if (str[cmd->index] != '\0')
			cmd->index++;
	}
}

t_token	*ft_cmdtrim(char *str)
{
	int			indx;
	int			wd_count;
	t_token		*tokens;
	t_cmdsplit	cmd;

	init_cmdsplit(&cmd);
	indx = 0;
	wd_count = 0;
	wd_count = words_count(str, &cmd, indx);
	tokens = ft_calloc((wd_count), sizeof(t_token));
	if (!tokens)
	{
		ft_putstr_fd("Malloc\n", 2);
		return (NULL);
	}
	init_tokens(tokens, wd_count);
	cmd.wd_count = 0;
	cmd.index = 0;
	init_result(str, &cmd, tokens);
	return (tokens);
}
