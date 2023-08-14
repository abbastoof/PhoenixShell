/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:16:33 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/14 17:25:36 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(char *str, t_lexer *state, int var_flag)
{
	if (var_flag == 1 && !ft_isspace(str[state->i + 1]) && str[state->i \
		+ 1] != '\0')
	{
		state->i++;
		if ((ft_isdigit(str[state->i]) && var_flag == 1)
			|| (ft_isquote(str[state->i]) && var_flag))
		{
			state->i++;
			return (1);
		}
	}
	else if (var_flag == 1 && (!ft_isspace(str[state->i + 1]) || str[state->i
				+ 1] == '\0' || ft_isquote(str[state->i + 1])))
	{
		state->i++;
		return (2);
	}
	return (0);
}

static int	malloc_error(char *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Malloc var finder\n", 2);
		return (1);
	}
	return (0);
}

static void	extract_var(char *str, int indx, t_lexer *state, char *des)
{
	while (!ft_isspace(str[indx]) && str[indx] != '\0' && !ft_isquote(str[indx])
		&& (str[indx] == '_' || ft_isalnum(str[indx])))
		indx++;
	state->var = ft_strnjoin(des, (str + state->i), indx - state->i);
}

char	*var_finder(char *str, t_lexer *state, t_env **env, int var_flag)
{
	int		indx;
	char	*des;
	int		checker_result;

	checker_result = checker(str, state, var_flag);
	if (checker_result == 1)
		return (NULL);
	else if (checker_result == 2)
		return ("$");
	indx = state->i;
	des = ft_calloc(1, 1);
	if (malloc_error(des))
		return (NULL);
	extract_var(str, indx, state, des);
	if (malloc_error(state->var))
		return (NULL);
	free(des);
	des = NULL;
	state->i = indx;
	if (var_flag == 1)
		return (find_path(env, state->var));
	else
		return (state->var);
}
