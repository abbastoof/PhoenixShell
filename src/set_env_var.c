/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:34:47 by mtoof             #+#    #+#             */
/*   Updated: 2023/05/22 15:37:52 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strjoin_inplace(char *dest, const char *s1, const char *s2)
{
	while (*s1)
		*dest++ = *s1++;
	*dest++ = '=';
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
}

void	set_environment_variable(const char *name, const char *value,
			char **env)
{
	int		i;
	char	*new_value;
	char	**new_environ;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], name, ft_strlen(name)) != 0
			|| env[i][ft_strlen(name)] != '='))
		i++;
	new_value = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (new_value == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	ft_strjoin_inplace(new_value, name, value);
	if (env[i])
	{
		// free(env[i]);
		env[i] = new_value;
	}
	else
	{
		new_environ = malloc((i + 2) * sizeof(char *));
		if (new_environ == NULL)
		{
			perror("minishell: malloc");
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new_environ, env, i * sizeof(char *));
		new_environ[i] = new_value;
		new_environ[i + 1] = NULL;
		free(env);
		env = new_environ;
	}
}
