/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:57:08 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:39:05 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_signalisation(void)
{
	struct sigaction	ctrl_c;

	sigemptyset(&ctrl_c.sa_mask);
	ctrl_c.sa_handler = signal_handler;
	ctrl_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ctrl_c, NULL);
	signal(SIGINT, signal_handler);
	sigaction(SIGQUIT, &ctrl_c, NULL);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, SIG_IGN);
}

void	ft_signalisation_under(void)
{
	struct sigaction	ctrl_c;

	sigemptyset(&ctrl_c.sa_mask);
	ctrl_c.sa_handler = signal_handler_under;
	ctrl_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ctrl_c, NULL);
	signal(SIGINT, signal_handler_under);
	sigaction(SIGQUIT, &ctrl_c, NULL);
	signal(SIGQUIT, signal_handler_under);
	signal(SIGTERM, SIG_IGN);
}

void	signal_handler_under(int signo)
{
	int				g_exit_under;
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	if (signo == SIGINT)
		g_exit_under = -1;
	else if (signo == SIGQUIT)
		return ;
	return ;
}
