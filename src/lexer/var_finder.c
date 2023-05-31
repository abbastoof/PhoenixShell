/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:16:33 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/31 20:22:22 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

char	*var_finder(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	int		indx;
	char	*des;

	if (var_flag == 1 && !ft_isspace(str[state->i + 1]) && str[state->i
			+ 1] != '\0' && str[state->i + 1] != '\"')
		state->i++;
	else if (var_flag == 1 && (!ft_isspace(str[state->i + 1]) || str[state->i
				+ 1] == '\0' || str[state->i + 1] == '\"'))
	{
		state->i++;
		return ("$");
	}
	indx = state->i;
	if (ft_isdigit(str[indx]) && var_flag == 1)
	{
		state->i++;
		return (NULL);
	}
	des = ft_calloc(1, 1);
	if (!des)
		return (NULL);
	while (str[indx] != ' ' && str[indx] != '\t' && str[indx] != '\0'
		&& str[indx] != '\'' && str[indx] != '\"')
		indx++;
	state->var = ft_strnjoin(des, (str + state->i), indx - state->i);
	free(des);
	des = NULL;
	state->i = indx;
	printf("str = %s\n", str + state->i);
	if (var_flag == 1)
		return (find_path(env->env_var, state->var));
	else
		return (state->var);
}
