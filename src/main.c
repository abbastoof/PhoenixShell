/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/05/22 12:58:43 by atoof            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	char			*cmd;
	t_environment	env;

	(void)ac;
	(void)av;
	initialize_environment(&env, environ);
	while (1)
	{
		cmd = readline("Minishell>");
		add_history(cmd);
		handle_command(&env, cmd);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
