/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/06/14 14:34:38 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_type(char *str, t_token *token, t_lexer *state)
{
	if (ft_strcmp(str, "|") == 0)
		token[state->token_indx].type = TOKEN_PIPE;
	else if (ft_strcmp(str, "<") == 0)
		token[state->token_indx].type = TOKEN_INPUT;
	else if (ft_strcmp(str, ">") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT;
	else if (ft_strcmp(str, ">>") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT_APPEND;
	else if (ft_strcmp(str, "<<") == 0)
		token[state->token_indx].type = TOKEN_HEREDOC;
	else
		token[state->token_indx].type = TOKEN_CMD;
	token[state->token_indx].value = ft_strdup(str);
	state->token_indx++;
}

static void	init_info(t_lexer *state)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->path = NULL;
	state->var = NULL;
	state->tmp = NULL;
	state->res = NULL;
	state->des = NULL;
	state->token_indx = 0;
}

// t_token	*lexer(char *line, t_env *env)
// {
// 	t_lexer	state;

// 	init_info(&state, line);
// 	while (state.crnt_str[state.indx])
// 	{
// 		if (state.crnt_str[state.indx] == '\'' && !state.indquote)
// 			is_word(state.crnt_str + state.indx, &state, env, 0);
// 		else if (state.crnt_str[state.indx] == '\"' && !state.inquote)
// 			is_word(state.crnt_str + state.indx, &state, env, 1);
// 		else if (((state.crnt_str[state.indx] == ' ')
// 				|| (state.crnt_str[state.indx] == '\t')) && (!state.inquote)
// 			&& (!state.indquote))
// 		{
// 			assign_token_type(state.start, state.token, &state);
// 			state.start = &state.crnt_str[state.indx + 1];
// 		}
// 		state.indx++;
// 	}
// 	assign_token_type(state.start, &(state.token[state.token_indx]), &state);
// 	return (state.token);
// }

// void	print_paths(t_lst *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst->cmd_paths[i] != NULL)
// 	{
// 		printf("%s\n", lst->cmd_paths[i]);
// 		i++;
// 	}
// }

void	process_cmd(char *line, t_env *env)
{
	t_token	*tokens;
	t_lexer	state;
	t_lst	lst;
	int		i;

	lst.paths = NULL;
	lst.cmd_paths = NULL;
	init_info(&state);
	(void)env;
	if (line[0] == '\0')
		return ;
	tokens = NULL;
	tokens = ft_cmdtrim(line, tokens);
	if (!check_incorrect_quotes(tokens))
	{
		expand_quotes(tokens, env, &state);
		get_command_paths(&lst, env);
		i = 0;
		while (tokens[i].value)
		{
			if (tokens[i].type == 0)
			{
				get_command_arguments(&lst, &tokens[i]);
				if (tokens[i].type == 1)
				{
					if (tokens[i + 1].value == NULL)
						break ;
					i++;
					while (tokens[i].value && (redirectors(tokens[i].value,
								0) == 0))
					{
						tokens[i].type = TOKEN_ARG;
						i++;
					}
					if (tokens[i].value == NULL)
						break ;
				}
			}
			i++;
		}
		display_token(tokens);
	}
}
