/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:59:59 by atoof             #+#    #+#             */
/*   Updated: 2023/05/24 14:00:25 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_environment(t_environment *env, char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	env->counter = i;
	env->env_var = malloc(sizeof(char *) * (i + 1));
	if (env->env_var == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "OLDPWD", 6) != NULL)
			i++;
		env->env_var[i] = ft_strdup(environ[i]);
		if (env->env_var[i] == NULL)
		{
			perror("minishell: strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
