/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/05/30 17:50:15 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chrjoin(char const *s1, char const s2)
{
	size_t	len1;
	size_t	i;
	char	*sjoin;

	if (s1)
	{
		len1 = ft_strlen(s1);
		sjoin = (char *)malloc(sizeof(char) * (len1 + 2));
		if (!sjoin)
			return (NULL);
		i = -1;
		while (s1[++i])
			sjoin[i] = s1[i];
		sjoin[len1] = s2;
		len1++;
		sjoin[len1] = '\0';
		return (sjoin);
	}
	return (NULL);
}

void	handledquote(char *str, t_lexer *state)
{
	if (str[state->i] == '\"' && !state->inquote)
	{
		if (str[state->i] == '\"' && state->flag == 0)
		{
			state->flag = 2;
			state->i++;
			state->indquote = 1;
		}
		if (str[state->i] == '\"' && state->flag == 2)
		{
			state->flag = 0;
			state->i++;
			state->indquote = 0;
		}
	}
}

void	handlequote(char *str, t_lexer *state)
{
	if (str[state->i] == '\'' && !state->indquote)
	{
		if (str[state->i] == '\'' && state->flag == 0)
		{
			state->flag = 1;
			state->i++;
			state->inquote = 1;
		}
		if (str[state->i] == '\'' && state->flag == 1)
		{
			state->flag = 0;
			state->i++;
			state->inquote = 0;
		}
	}
	handledquote(str, state);
}

void	join_char(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	char	*var;
	int		str_indx;

	str_indx = state->i;
	if (state->tmp == NULL)
	{
		state->tmp = malloc(sizeof(char) * 2);
		if (!state->tmp)
			return ;
	}
	if (str[state->i] == '$')
		state->path = var_finder(str, state, env, var_flag);
	if (state->path != NULL)
	{
		
	}
	state->res = ft_chrjoin(state->tmp, str[state->i]);
	if (state->tmp)
		free(state->tmp);
	state->tmp = state->res;
	state->i++;
}

int	is_word(char *str, t_lexer *state, t_environment *env, int var_flag)
{
	state->flag = 0;
	state->i = 0;
	while (str[state->i] == ' ' || str[state->i] == '\t')
		state->i++;
	while (str[state->i])
	{
		handlequote(str, state);
		if ((str[state->i] && state->flag == 0 && str[state->i] != ' ')
			&& (str[state->i] != '\'') && (str[state->i] != '\"'))
			join_char(str, state, env, var_flag);
		else if ((str[state->i] && (state->flag == 1 && str[state->i] != '\''))
			|| (str[state->i] && (state->flag == 2 && str[state->i] != '\"')))
			join_char(str, state, env, var_flag);
		else if (state->flag == 0 && str[state->i] == ' ')
			break ;
	}
	//TODO: ERROR HANDLING
	if (state->flag == 1)
		ft_putstr_fd("The quote is not closed\n", 2);
	else if (state->flag == 2)
		ft_putstr_fd("The double quotes are not closed\n", 2);
	//TODO: ERROR HANDLING
	return (0);
}
