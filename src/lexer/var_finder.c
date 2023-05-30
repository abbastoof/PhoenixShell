/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:16:33 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/30 23:26:28 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_finder(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	char	*var;
	char	*des;
	char	*path;

	if (!des)
	{
		des = ft_calloc(1, 1);
		if (!des)
			return (NULL);
	}
	if (var_flag == 1)
		state->i++;
	if (!ft_isalpha(str[state->i]) && var_flag == 1)
		return (NULL);
	while (str[state->i] != ' ' || str[state->i] != '\t'
		|| str[state->i] != '\0')
	{
		var = ft_chrjoin(des, str[state->i]);
		if (des)
			free(des);
		des = var;
		state->i++;
	}
	if (var_flag == 1)
		return (find_path(env, des));
	else
		return (des);
}
