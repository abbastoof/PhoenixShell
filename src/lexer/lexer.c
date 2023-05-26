/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/05/26 13:14:56 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_type(char *str, t_token *token)
{
	if (strcmp(str, "|") == 0)
		token->type = TOKEN_PIPE;
	else if (strcmp(str, "<") == 0)
		token->type = TOKEN_INPUT;
	else if (strcmp(str, ">") == 0)
		token->type = TOKEN_OUTPUT;
	else if (strcmp(str, ">>") == 0)
		token->type = TOKEN_OUTPUT_APPEND;
	else if (strcmp(str, "<<") == 0)
		token->type = TOKEN_HEREDOC;
	else if (str[0] == '$')
	{
		if (strcmp(str, "$?") == 0)
			token->type = TOKEN_EXIT_STATUS;
		else
			token->type = TOKEN_VARIABLE;
	}
	else
	{
		token->type = TOKEN_CMD;
	}
}

static void	handlequote(t_lexer *state, int type)
{
	int	*flag;

	flag = 0;

	if (type == TOKEN_QUOTE)
		flag = &(state->inquote);
	else if (type == TOKEN_DQUOTE)
		flag = &(state->indquote);
	*flag = 1;
	
}

static void	init_info(t_lexer *state, char *line)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->start = line;
	state->crnt_str = line;
	state->token = malloc(sizeof(t_token) * 1024);
}

t_token	*lexer(char *line)
{
	t_lexer	state;

	init_info(&state, line);
	while (state.crnt_str[state.indx])
	{
		if (state.crnt_str[state.indx] == ' ' || '\t' && !state.inquote
			&& !state.indquote)
		{
			while (state.crnt_str[state.indx] == ' ' || '\t')
			{
				state.indx++;
				state.start++;
			}
		}
		if (state.crnt_str[state.indx] == '\'' && !state.indquote)
			handlequote(&state, TOKEN_QUOTE);
		else if (state.crnt_str[state.indx] == '\"' && !state.inquote)
			handlequote(&state, TOKEN_DQUOTE);
		state.indx++;
	}
}

void	process_cmd(char *line)
{
	t_token	*tokens;

	tokens = lexer(line);
	// handle_command(tokens);
}
