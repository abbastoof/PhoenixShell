/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/07/19 12:49:47 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char				*cmd;
	t_env				env;

	(void)ac;
	(void)av;
	g_stdout = dup(STDOUT_FILENO);
	g_stdin = dup(STDIN_FILENO);
	initialize_environment(&env, envp);
	while (1)
	{
		disable_enable_ctl(0);
		init_signals();
		cmd = readline("Minishell>");
		add_history(cmd);
		if (cmd == NULL)
			ctrl_d_handler();
		process_cmd(cmd, &env);
		signal(SIGINT, SIG_IGN);
		disable_enable_ctl(1);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
