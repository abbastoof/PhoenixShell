/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:16:33 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/30 11:35:38 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_finder(char *str, t_lexer *state, t_environment *env)
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
	if (str[state->i] == '$')
		state->i++;
	while (str[state->i] != ' ' || str[state->i] != '\t'
		|| str[state->i] != '\0')
	{
		var = ft_chrjoin(des, str[state->i]);
		if (des)
			free(des);
		des = var;
		state->i++;
	}
	path = find_path(env, des);
	free(des);
	return (path);
}
