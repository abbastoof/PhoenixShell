/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:25:14 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/24 13:07:20 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	word_contain_quote_2(char *str, t_cmdsplit *cmd)
{
	int		quote_num;

	cmd->quote = str[cmd->index];
	cmd->index++;
	quote_num = 1;
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] == cmd->quote)
			quote_num++;
		if ((quote_num % 2) == 0 && (ft_isspace(str[cmd->index + 1]) \
			|| str[cmd->index + 1] == '\0' || redirectors(str, cmd->index \
			+ 1)))
			break ;
		cmd->index++;
		if (quote_num % 2 == 0)
		{
			if (ft_isquote(str[cmd->index]))
			{
				cmd->quote = str[cmd->index];
				quote_num = 1;
				cmd->index++;
			}
		}
	}
}

static void	word_contain_quote(char *str, t_cmdsplit *cmd)
{
	int		quote_num;

	quote_num = 1;
	while (str[cmd->index] != '\0')
	{
		if (str[cmd->index] == cmd->quote)
			quote_num++;
		if ((quote_num % 2) == 0 && (ft_isspace(str[cmd->index + 1]) \
			|| str[cmd->index + 1] == '\0' || redirectors(str, cmd->index \
			+ 1)))
			break ;
		cmd->index++;
		if (quote_num % 2 == 0)
		{
			if (ft_isquote(str[cmd->index]))
			{
				cmd->quote = str[cmd->index];
				quote_num = 1;
				cmd->index++;
			}
		}
	}
}

int	split_quote(char *str, t_cmdsplit *cmd, t_token **tokens)
{
	t_token	*new;

	new = new_token();
	if (!new)
		return (-1);
	cmd->quote = str[cmd->index];
	cmd->start = cmd->index;
	cmd->index++;
	word_contain_quote(str, cmd);
	new->value = ft_substr(str, cmd->start, (cmd->index - cmd->start) + 1);
	if (!new->value)
		return (-1);
	if (ft_token_add_back(tokens, new) == -1)
		return (-1);
	return (0);
}
