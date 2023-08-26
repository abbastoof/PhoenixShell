/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/08/26 13:20:39 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	g_exit_status = 0;
	init_env(&env, envp);
	while (1)
	{
		echoing_control_chars(0);
		init_signals(1);
		cmd = readline("Minishell>");
		if (cmd == NULL)
			ctrl_d_handler();
		echoing_control_chars(1);
		if (cmd != NULL && cmd[0] != 0)
			add_history(cmd);
		process_cmd(cmd, &env);
		if (cmd != NULL)
			free(cmd);
	}
	free_env(&env);
	return (0);
}
