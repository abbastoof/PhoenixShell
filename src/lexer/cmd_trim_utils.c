/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:46:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/06 11:55:47 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirectors(char *str, t_cmdsplit *cmd)
{
	cmd->res = redirectors(str, cmd->index);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
		cmd->index++;
	else if (cmd->res == TOKEN_VARIABLE)
	{
		while (str[cmd->index] != '\0' && !ft_isspace(str[cmd->index]))
			cmd->index++;
	}
	cmd->wd_count++;
}

void	check_isquote(char *str, t_cmdsplit *cmd)
{
	cmd->quote = str[cmd->index];
	cmd->index++;
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] == cmd->quote && (ft_isspace(str[cmd->index
						+ 1]) || str[cmd->index + 1] == '\0'
				|| redirectors(str, cmd->index + 1)))
			break ;
		cmd->index++;
	}
	cmd->wd_count++;
}
