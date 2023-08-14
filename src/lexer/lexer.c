/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 18:25:16 by atoof            ###   ########.fr       */
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

void	process_cmd(char *line, t_env **env)
{
	t_token	*tokens;
	t_lexer	state;
	t_tree	*tree;
	int		res;

	res = 0;
	tree = NULL;
	init_info(&state);
	(void)env;
	if (line[0] == '\0')
		return ;
	tokens = NULL;
	tokens = ft_cmdtrim(line, tokens);
	if (check_quotes_syntax(tokens) != 0)
	{
		g_tree.exit_status = 258;
		free_tokens(tokens);
		return ;
	}
	else
	{
		expand_quotes(tokens, env, &state);
		if (create_tree(&tokens, &tree) == -1)
			free_tree(&tree);
		free_tokens(tokens);
	}
	res = check_for_heredoc(&tree);
	if (res == 0)
		exec_tree(&tree, env, getpid());
	if (tree)
		free_tree(&tree);
	tree = NULL;
}
