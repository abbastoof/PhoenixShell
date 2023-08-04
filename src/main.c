/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 15:08:16 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **envp)
{
	char				*cmd;
	t_env				*env;

	(void)ac;
	(void)av;
	env = NULL;
	g_tree.standard_input = dup(STDIN_FILENO);
	g_tree.standard_output = dup(STDOUT_FILENO);
	init_env(&env, envp);
	while (1)
	{
		echoing_control_chars(0);
		init_signals(1);
		cmd = readline("Minishell>");
		add_history(cmd);
		if (cmd == NULL)
			ctrl_d_handler();
		process_cmd(cmd, &env);
		signal(SIGINT, SIG_IGN);
		echoing_control_chars(1);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
