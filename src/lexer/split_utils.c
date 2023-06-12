/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:46:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/12 16:44:41 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirectors(char *str, int i)
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
	else if (str[i] == '$')
	{
		if (ft_strncmp(str + i, "$?", 2) == 0)
			return (TOKEN_EXIT_STATUS);
	}
	return (0);
}

void	init_cmdsplit(t_cmdsplit *cmd)
{
	cmd->index = 0;
	cmd->index = 0;
	cmd->quote = 0;
	cmd->res = 0;
	cmd->wd_count = 0;
}

void	check_redirectors(char *str, t_cmdsplit *cmd)
{
	cmd->res = redirectors(str, cmd->index);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
		cmd->index++;
}

int	check_isquote(char *str, t_cmdsplit *cmd)
{
	cmd->quote = str[cmd->index];
	cmd->index++;
	if (str[cmd->index] == '\0')
		return (1);
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] == cmd->quote && (ft_isspace(str[cmd->index + 1])
				|| str[cmd->index + 1] == '\0' || redirectors(str, cmd->index
					+ 1)))
			break ;
		cmd->index++;
	}
	return (0);
}

int	words_count(char *str, t_cmdsplit *cmd)
{
	while (str[cmd->index] != '\0')
	{
		if (!ft_isspace(str[cmd->index]) && redirectors(str, cmd->index) == 0
			&& !ft_isquote(str[cmd->index]))
		{
			while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index])
				&& redirectors(str, cmd->index) == 0)
				cmd->index++;
			cmd->wd_count++;
		}
		if (redirectors(str, cmd->index) != 0)
		{
			check_redirectors(str, cmd);
			cmd->wd_count++;
		}
		if (ft_isquote(str[cmd->index]))
		{
			if (!check_isquote(str, cmd))
				cmd->wd_count++;
		}
		if (str[cmd->index] != '\0')
			cmd->index++;
	}
	return (cmd->wd_count);
}
