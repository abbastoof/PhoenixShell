/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:34 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/07 17:28:33 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote(char *str, t_cmdsplit *cmd)
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
	cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
				- cmd->start) + 1);
}

static void	handle_redirector(char *str, t_cmdsplit *cmd)
{
	cmd->start = cmd->index;
	cmd->res = redirectors(str, cmd->index);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
	{
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, ((cmd->index
						+ 2) - cmd->start));
		cmd->index++;
	}
	else
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, ((cmd->index
						+ 1) - cmd->start));
}

static void	handle_word(char *str, t_cmdsplit *cmd)
{
	cmd->start = cmd->index;
	while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
		&& redirectors(str, cmd->index) == 0)
		cmd->index++;
	cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
				- cmd->start));
}

static void	init_result(char *str, t_cmdsplit *cmd)
{
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] && !ft_isspace(str[cmd->index]) && (redirectors(str,
					cmd->index) == 0 && !ft_isquote(str[cmd->index])))
		{
			handle_word(str, cmd);
			cmd->wd_count++;
		}
		if (str[cmd->index] && redirectors(str, cmd->index))
		{
			handle_redirector(str, cmd);
			cmd->wd_count++;
		}
		if (str[cmd->index] && (ft_isquote(str[cmd->index])))
		{
			handle_quote(str, cmd);
			cmd->wd_count++;
		}
		if (str[cmd->index] != '\0')
			cmd->index++;
	}
}

char	**ft_cmdtrim(char *str)
{
	int			indx;
	int			wd_count;
	t_cmdsplit	cmd;

	init_cmdsplit(&cmd);
	cmd.result = NULL;
	indx = 0;
	wd_count = 0;
	wd_count = words_count(str, &cmd, indx);
	printf("word count is: %d\n", wd_count);
	cmd.result = ft_calloc((wd_count + 1), sizeof(char *));
	if (!cmd.result)
		return (NULL);
	wd_count = 0;
	cmd.index = 0;
	init_result(str, &cmd);
	printf("cmd->word count is: %d\n", cmd.wd_count);
	return (cmd.result);
}
