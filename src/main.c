/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:43 by atoof             #+#    #+#             */
/*   Updated: 2023/06/05 11:38:05 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char			*cmd;
	t_env			env;
	char			**res;

	(void)ac;
	(void)av;
	initialize_environment(&env, environ);
	while (1)
	{
		cmd = readline("Minishell>");
		add_history(cmd);
		res = ft_cmdtrim(cmd);
		int	i = -1;
		while (res[++i])
		{
			printf("%s\n", res[i]);
			free(res[i]);
		}
		free(res);
		// handle_command(&env, cmd);
		// process_cmd(cmd, &env);
		free(cmd);
	}
	free_env(&env);
	return (0);
}
