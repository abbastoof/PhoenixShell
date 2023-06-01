/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:16:33 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/01 16:09:33 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(char *str, t_lexer *state, int var_flag)
{
	if (var_flag == 1 && !ft_isspace(str[state->i + 1]) && str[state->i
			+ 1] != '\0' && str[state->i + 1] != '\"'
		&& str[state->i + 1] != '\\')
		state->i++;
	else if (var_flag == 1 && (!ft_isspace(str[state->i + 1]) || str[state->i
				+ 1] == '\0' || str[state->i + 1] == '\"'))
	{
		state->i++;
		return (2);
	}
	return (0);
}

char	*var_finder(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	int		indx;
	char	*des;

	if (checker(str, state, var_flag) == 2)
		return ("$");
	indx = state->i;
	if (ft_isdigit(str[indx]) && var_flag == 1)
	{
		state->i++;
		return (NULL);
	}
	des = ft_calloc(1, 1);
	if (!des)
		return (NULL);
	while (!ft_isspace(str[indx]) && str[indx] != '\0'
		&& !ft_isquote(str[indx]))
		indx++;
	state->var = ft_strnjoin(des, (str + state->i), indx - state->i);
	free(des);
	des = NULL;
	state->i = indx;
	if (var_flag == 1)
		return (find_path(env->env_var, state->var));
	else
		return (state->var);
}
