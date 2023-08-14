/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/08/14 20:21:56 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execute_command(t_tree **tree, t_env **env)
{
	int	res;

	res = 0;
	res = check_for_heredoc(tree);
	if (res == 0)
		exec_tree(tree, env, getpid());
	if (tree)
	{
		free_tree(tree);
		tree = NULL;
	}
}

static void	syntax_expantion(t_token *tokens, t_lexer state, t_tree **tree, \
t_env **env)
{
	if (check_quotes_syntax(tokens) != 0)
	{
		g_tree.exit_status = 258;
		free_tokens(tokens);
		return ;
	}
	else
	{
		expand_quotes(tokens, env, &state);
		if (create_tree(&tokens, tree) == -1)
			free_tree(tree);
		free_tokens(tokens);
	}
}

void	process_cmd(char *line, t_env **env)
{
	t_token	*tokens;
	t_lexer	state;
	t_tree	*tree;

	tree = NULL;
	init_info(&state);
	if (line[0] == '\0')
		return ;
	tokens = NULL;
	tokens = ft_cmdtrim(line, tokens);
	if (tokens == NULL)
		return ;
	syntax_expantion(tokens, state, &tree, env);
	execute_command(&tree, env);
}
