/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:56:57 by atoof             #+#    #+#             */
/*   Updated: 2023/06/01 17:56:38 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_command(t_environment *env, const char *cmd)
// {
// 	char	**tokens;
// 	char	**ptr;
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	tokens = ft_split(cmd, ' ');
// 	if (tokens != NULL && tokens[0] != NULL)
// 	{
// 		if (ft_strcmp(tokens[0], "cd") == 0)
// 		{
// 			path = tokens[1];
// 			ft_cd(env, path);
// 		}
// 		else if (ft_strcmp(tokens[0], "export") == 0)
// 		{
// 			ptr = ft_realloc(env->env_var, env->counter + 2);
// 			free(env->env_var);
// 			env->env_var = ptr;
// 		}
// 		else if (ft_strcmp(tokens[0], "env") == 0)
// 		{
// 			while (env->env_var[++i])
// 				printf("%s\n", env->env_var[i]);
// 		}
// 		else if (ft_strcmp(tokens[0], "echo") == 0)
// 			echo(tokens + 1);
// 		else if (ft_strcmp(tokens[0], "pwd") == 0)
// 			pwd();
// 		free(tokens);
// 	}
// }

void	handle_command(t_env *env, t_token *tokens)
{
	int		i;
	t_token	*token;
	t_lexer	*state;

	state = NULL;
	i = 0;
	token = tokens;
	while (token->value != NULL)
	{
		if (token->type == TOKEN_CMD)
		{
			if (ft_strcmp(token->value, "cd") == 0)
				ft_cd(env, state->start);
			else if (ft_strcmp(token->value, "export") == 0)
			{
			}
			else if (ft_strcmp(token->value, "env") == 0)
			{
				while (env->env_var[++i])
					printf("%s\n", env->env_var[i]);
			}
			else if (ft_strcmp(token->value, "echo") == 0)
			{
			}
			else if (ft_strcmp(token->value, "pwd") == 0)
				pwd();
			// else if ()
		}
		token++;
	}
}
