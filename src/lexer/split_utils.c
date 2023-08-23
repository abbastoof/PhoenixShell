/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:46:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 19:45:41 by mtoof            ###   ########.fr       */
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

int	ft_token_add_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	last = *tokens;
	if (!tokens || !new)
		return (-1);
	if (*tokens == NULL)
	{
		*tokens = new;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (0);
}

t_token	*new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		ft_putstr_fd("Malloc new _token\n", 2);
		return (NULL);
	}
	new->value = NULL;
	new->type = 0;
	new->next = NULL;
	return (new);
}
