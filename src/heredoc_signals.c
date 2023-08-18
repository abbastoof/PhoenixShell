/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:11:31 by atoof             #+#    #+#             */
/*   Updated: 2023/08/18 12:20:44 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(1);
}

void	heredoc_signals(void)
{
	struct sigaction	sa;

	echoing_control_chars(0);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
