/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/05/25 12:55:49 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
