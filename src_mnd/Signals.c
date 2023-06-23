/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:55:49 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 20:19:26 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	kill_fork(int id)
{
	write(2, "\033[32mExit", 10);
	kill(id, SIGINT);
}

int	exit_cmp(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	sin_int_handler(int sig_num)
{
	(void) sig_num;
	exit(0);
}

void	sin_term_handler(int sig_num)
{
	(void) sig_num;
	exit(0);
}

void	signal_handler(int signo)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		return ;
}
