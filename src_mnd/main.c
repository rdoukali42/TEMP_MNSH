/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:38 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/15 22:19:01 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	**ft_exe(char *line, char **env, t_mnsh *minishell)
{
	line = ft_space_erase2(line, minishell);
	if (ft_strchr(line, '>') || ft_strchr(line, '<'))
		env = ft_exec_redir(line, env, minishell);
	else
		env = ft_builtin(line, env, minishell);
	return (env);
}

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

void	ft_rl(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "exit\n", 5);
}

int	**ft_execute(char *line, t_mnsh *minishell)
{
	char	**all;

	if (ft_check_quote(line, '\''))
		ft_quote(line, minishell->env, '\'', minishell);
	else if (ft_check_quote(line, '\"'))
		ft_quote(line, minishell->env, '\"', minishell);
	else if (ft_strchr_pipe(line, '|'))
	{
		all = ft_split(line, '|', minishell);
		minishell->env = ft_pipe(line, minishell->env, all, minishell);
	}
	else
	{
		if (ft_strchr_pipe(line, '>') || ft_strchr_pipe(line, '<'))
			ft_exec_redir(line, minishell->env, minishell);
		else
			minishell->env = ft_builtin(line, minishell->env, minishell);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	static int	a;
	char		*line;
	char		*path;
	t_mnsh		minishell;

	a = 0;
	minishell.exit = 0;
	minishell.memory_blocks = NULL;
	if (a == 0)
		minishell.env = ft_file_dup(envp, &minishell);
	a = 1;
	while (1)
	{
		ft_signalisation();
		line = readline("ᴍɪɴɪꜱʜᴇʟʟ -> ");
		if (!line)
		{
			ft_rl ();
			break ;
		}
		if (line[0] == 0)
			continue ;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		ft_execute(line, &minishell);
		add_history(line);
		rl_on_new_line();
	}
	free_path(minishell.env, &minishell);
	free_all_mem(&minishell.memory_blocks);
	return (minishell.exit);
}
