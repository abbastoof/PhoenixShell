/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:34 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/06 11:52:09 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirectors(char *str, int i)
{
	if (ft_strncmp(str + i, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str + i, ">>", 2) == 0)
		return (TOKEN_OUTPUT_APPEND);
	else if (ft_strncmp(str + i, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(str + i, "<", 1) == 0)
		return (TOKEN_INPUT);
	else if (ft_strncmp(str + i, ">", 1) == 0)
		return (TOKEN_OUTPUT);
	else
		return (0);
}

static int	words_count(const char *str, t_cmdsplit *cmd)
{
	while (str[cmd->index] != '\0')
	{
		if (!ft_isspace(str[cmd->index]) && redirectors(str, cmd->index) == 0)
		{
			while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
				&& redirectors(str, cmd->index) == 0)
				cmd->index++;
			cmd->wd_count++;
		}
		if (redirectors(str, cmd->index) != 0)
			check_redirectors(str, cmd);
		if (ft_isquote(str[cmd->index]))
			check_isquote(str, cmd);
		cmd->index++;
	}
	return (cmd->wd_count);
}

static void	init_cmdsplit(t_cmdsplit *cmd)
{
	cmd->index = 0;
	cmd->index = 0;
	cmd->quote = 0;
	cmd->res;
	cmd->result = NULL;
	cmd->wd_count = 0;
}

static void	init_result(char const *str, t_cmdsplit *cmd)
{
	if (str[cmd->index] == '\'' || str[cmd->index] == '"')
	{
		cmd->quote = str[cmd->index];
		cmd->start = cmd->index;
		cmd->index++;
		while (str[cmd->index] != '\0' && str[cmd->index] != cmd->quote)
			cmd->index++;
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
					- cmd->start) + 1);
		cmd->wd_count++;
	}
	else if (str[cmd->index] != ' ')
	{
		cmd->start = cmd->index;
		while (str[cmd->index] != '\0' && str[cmd->index] != ' '
			&& str[cmd->index] != '\'' && str[cmd->index] != '"')
			cmd->index++;
		cmd->result[cmd->wd_count] = ft_substr(str, cmd->start, (cmd->index
					- cmd->start) + 1);
		cmd->wd_count++;
	}
}

char	**ft_cmdtrim(char const *str)
{
	t_cmdsplit	cmd;

	init_cmdsplit(&cmd);
	cmd.wd_count = words_count(str, &cmd);
	cmd.result = ft_calloc((cmd.wd_count + 1), sizeof(char *));
	if (!cmd.result)
		return (NULL);
	cmd.wd_count = 0;
	cmd.index = 0;
	while (str[cmd.index] != '\0')
	{
		init_result(str, &cmd);
		cmd.index++;
	}
	return (cmd.result);
}
