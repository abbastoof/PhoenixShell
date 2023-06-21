/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:44:57 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/20 20:06:16 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_state(t_lexer *state)
{
	if (state->tmp != NULL)
	{
		free(state->tmp);
		state->tmp = NULL;
	}
	if (state->res != NULL)
		state->res = NULL;
	if (state->var != NULL)
	{
		free(state->var);
		state->var = NULL;
	}
	if (state->path != NULL)
		state->path = NULL;
	if (state->des != NULL)
	{
		free(state->des);
		state->des = NULL;
	}
}

void	free_tokens(t_token *tokens)
{
	int	indx;

	indx = 0;
	if (tokens[indx].value)
	{
		while (tokens[indx].value != NULL)
		{
			free(tokens[indx].value);
			tokens[indx].value = NULL;
			indx++;
		}
		free(tokens);
		tokens = NULL;
	}
	return ;
}

void	free_cmd_struct(t_cmd *cmd)
{
	int	indx;

	indx = 0;
	if (cmd->paths)
		cmd->paths = NULL;
	if (cmd->cmd_paths)
	{
		while (cmd->cmd_paths[indx])
		{
			free(cmd->cmd_paths[indx]);
			cmd->cmd_paths[indx] = NULL;
			indx++;
		}
		free(cmd->cmd_paths);
		cmd->cmd_paths = NULL;
	}
	if (cmd->cmd)
		cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->cmd_arguments = NULL;
	cmd->cmd_paths = NULL;
	cmd->paths = NULL;
}
