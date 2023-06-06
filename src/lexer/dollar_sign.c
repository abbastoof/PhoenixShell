/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:43:23 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/06 13:02:12 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	result_join(t_lexer *state, char *str)
{
	state->res = ft_strnjoin(state->tmp, str + state->i, 1);
	if (state->tmp)
		free(state->tmp);
	state->tmp = state->res;
	state->i++;
}

static void	dollar_handler_util(t_lexer *state, int var_flag)
{
	if (state->path != NULL)
	{
		printf("strlen path = %d\n", (int)ft_strlen(state->path));
		printf("strlen tmp = %d\n", (int)ft_strlen(state->tmp));
		printf("res = %s\n", ft_strjoin(state->tmp, state->path));
		if (state->path[0] == '=')
			state->path++;
		state->res = ft_strjoin(state->tmp, state->path);
		if (state->tmp)
			free(state->tmp);
		state->tmp = state->res;
		if (state->path && var_flag == 0)
			free(state->path);
	}
}

void	dollar_handler(char *str, t_lexer *state, t_env *env, int var_flag)
{
	if (str[state->i] == '$' && (str[state->i + 1] != '\\'
			&& (str[state->i + 1] != '%' && str[state->i + 1] != '!')))
	{
		state->path = var_finder(str, state, env, var_flag);
		printf("path = %s\n", (state->path));
		dollar_handler_util(state, var_flag);
	}
	else if (str[state->i] == '$' && (str[state->i + 1]
			== '\\' || (str[state->i
					+ 1] == '%')))
		result_join(state, str);
	else if (str[state->i] == '$' && (str[state->i + 1] == '!'))
		state->i++;
	else
		result_join(state, str);
}
