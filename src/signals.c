/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/21 19:28:24 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function: tcsetattr
 		the effects of the functions on the terminal do not
 		become effective, nor are all errors detected, until the
 		tcsetattr() function is called.
 		If optional_actions is TCSANOW, the change shall occur immediately.
*/

/* Macro: int SA_RESTART
		This flag controls what happens when a signal is delivered
		during certain primitives (such as open, read or write),
		and the signal handler returns normally. 
*/

/* If a signal is caught during the system calls listed below, the call may
     be forced to terminate with the error EINTR, the call may return with a
     data transfer shorter than requested, or the call may be restarted.
     Restart of pending calls is requested by setting the SA_RESTART bit in
     sa_flags.  The affected system calls include open(2), read(2), write(2),
     sendto(2), recvfrom(2), sendmsg(2) and recvmsg(2) on a communications
     channel or a slow device (such as a terminal, but not a regular file) and
     during a wait(2) or ioctl(2).  However, calls that have already committed
     are not restarted, but instead return a partial success (for example, a
     short read count).
 */

/* Function: rl_replace_line
		void rl_replace_line (const char *text, int clear_undo)
		Replace the contents of rl_line_buffer with text. The point and mark
		are preserved, if possible. If clear_undo is non-zero, the undo list
		associated with the current line is cleared.
*/

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
	exit(1);
}
