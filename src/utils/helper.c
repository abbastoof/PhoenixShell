/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:05:33 by atoof             #+#    #+#             */
/*   Updated: 2023/06/01 15:46:45 by atoof            ###   ########.fr       */
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

int        ft_isquote(int c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

void	ft_free_strarray(char **str_array)
{
	char	**temp;

	if (str_array == NULL)
		return ;
	temp = str_array;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(str_array);
}

char	*find_path(char **envp, char *str)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(str, *envp, ft_strlen(str)) == 0)
			return (*envp + ft_strlen(str));
		envp++;
	}
	return (NULL);
}

void	initialize_minishell(t_lst *line)
{
	line->pid = 0;
	line->end[0] = 0;
	line->end[1] = 0;
	line->infile = 0;
	line->outfile = 0;
	line->cmd_paths = NULL;
	line->cmd_arguments = NULL;
	line->cmd = NULL;
}

void	free_env(t_environment *env)
{
	int	i;

	i = -1;
	if (env->env_var)
	{
		while (env->env_var[++i])
			free(env->env_var[i]);
		free(env->env_var);
	}
}
