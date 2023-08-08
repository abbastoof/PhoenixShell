/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:35 by atoof             #+#    #+#             */
/*   Updated: 2023/08/08 11:09:57 by atoof            ###   ########.fr       */
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
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(int state)
{
	struct sigaction	sa;
	struct sigaction	s_quit;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (state == 1)
		sa.sa_handler = handle_signal;
	else if (state == 0)
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&s_quit.sa_mask);
	if (state == 1)
		s_quit.sa_handler = SIG_IGN;
	else if (state == 0)
		s_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &s_quit, NULL);
}

void	ctrl_d_handler(void)
{
	echoing_control_chars(1);
	write(1, "exit\n", 6);
	exit(1);
}

void	heredoc_signal_handler(int signal)
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
