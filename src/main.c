/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/06/13 14:39:08 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*cmd;
	t_env	env;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	initialize_environment(&env, environ);
	while (1)
	{
		cmd = readline("Minishell>");
		add_history(cmd);
		process_cmd(cmd, &env);
		// int	i = -1;
		// while (res[++i])
		// {
		// 	printf("%s\n", res[i]);
		// 	free(res[i]);
		// }
		// free(res);
		// handle_command(&env, cmd);
		// process_cmd(cmd, &env);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
