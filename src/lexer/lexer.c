/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/07/11 13:16:09 by atoof            ###   ########.fr       */
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

// static void	set_cmd_args_type(t_cmd *cmd, t_env *env, t_token *tokens)
// {
// 	int		i;

// 	get_command_paths(cmd, env);
// 	i = 0;
// 	while (tokens[i].value)
// 	{
// 		if (tokens[i].type == 0)
// 		{
// 			get_command_arguments(cmd, &tokens[i]);
// 			if (tokens[i].type == 1)
// 			{
// 				if (tokens[i + 1].value == NULL)
// 					break ;
// 				i++;
// 				while (tokens[i].value && tokens[i].type == 0)
// 				{
// 					tokens[i].type = TOKEN_ARG;
// 					i++;
// 				}
// 				if (tokens[i].value == NULL)
// 					break ;
// 			}
// 		}
// 		i++;
// 	}
// }

void	process_cmd(char *line, t_env *env)
{
	t_token	*tokens;
	t_lexer	state;
	t_tree	*tree;

	tree = NULL;
	init_info(&state);
	(void)env;
	if (line[0] == '\0')
		return ;
	tokens = NULL;
	tokens = ft_cmdtrim(line, tokens);
	if (!check_incorrect_quotes(tokens))
	{
		expand_quotes(tokens, env, &state);
		// display_token(tokens);
		if (create_tree(&tokens, &tree) == -1)
			free_tree(tree);
		free_tokens(tokens);
	}
	exec_tree(tree, env);
	// if (tree)
	// 	display_list(tree);
	// if (tree)
	// 	free_tree(tree);
	tree = NULL;
}
