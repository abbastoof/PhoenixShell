/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:05:33 by atoof             #+#    #+#             */
/*   Updated: 2023/05/22 11:57:25 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_free_strarray(char **str_array)
// {
// 	char	**temp;

// 	if (str_array == NULL)
// 		return ;
// 	temp = str_array;
// 	while (*temp != NULL)
// 	{
// 		free(*temp);
// 		temp++;
// 	}
// 	free(str_array);
// }

char	*find_path(char **envp, char *str)
{
	while (ft_strncmp(str, *envp, ft_strlen(str)))
		envp++;
	return (*envp + ft_strlen(str));
}

void	initialize_minishell(t_minishell *line)
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
