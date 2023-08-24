/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/08/24 14:24:30 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_lexer *state)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->condition_result = 0;
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
		exec_tree(tree, env, 1);
	if (tree)
	{
		free_tree(tree);
		tree = NULL;
	}
}

static int	syntax_expansion(t_token **tokens, t_lexer state, t_tree **tree, \
			t_env **env)
{
	if (check_quotes_syntax(tokens) != 0)
	{
		g_exit_status = 258;
		free_tokens(tokens);
		return (1);
	}
	else
	{
		if (expansion(tokens, &state, env))
			return (1);
		if (create_tree(tokens, tree) == -1)
		{
			free_tree(tree);
			free_tokens(tokens);
			return (1);
		}
	}
	if (tokens)
		free_tokens(tokens);
	return (0);
}

void	process_cmd(char *line, t_env **env)
{
	t_token	*tokens;
	t_lexer	state;
	t_tree	*tree;

	(void)env;
	tree = NULL;
	init_info(&state);
	if (line[0] == '\0')
		return ;
	tokens = NULL;
	if (ft_cmdtrim(line, &tokens) == -1)
		return ;
	if (tokens == NULL)
		return ;
	if (syntax_expansion(&tokens, state, &tree, env))
		return ;
	execute_command(&tree, env);
	if (tree)
		free_tree(&tree);
}
