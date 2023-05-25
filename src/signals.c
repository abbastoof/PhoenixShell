/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:35 by atoof             #+#    #+#             */
/*   Updated: 2023/05/25 11:58:26 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigquit_handler(int signum __attribute__((unused)))
{
	if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "Exit\n", 5);
		exit(0);
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGQUIT, sigquit_handler);
}
