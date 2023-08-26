/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/26 13:01:08 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echoing_control_chars(int enable)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (enable == 0)
		term.c_lflag &= ~(ECHOCTL);
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	init_signals(int state)
{
	struct sigaction	int_action;
	struct sigaction	quit_action;

	sigemptyset(&int_action.sa_mask);
	sigemptyset(&quit_action.sa_mask);
	int_action.sa_flags = SA_RESTART;
	if (state == 1)
	{
		int_action.sa_handler = handle_signal;
		quit_action.sa_handler = SIG_IGN;
	}
	else if (state == 0)
	{
		int_action.sa_handler = SIG_IGN;
		quit_action.sa_handler = SIG_DFL;
	}
	sigaction(SIGINT, &int_action, NULL);
	sigaction(SIGQUIT, &quit_action, NULL);
}

void	ctrl_d_handler(void)
{
	write(2, "exit\n", 6);
	exit(g_exit_status);
}
