/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:38 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:42:33 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"
#include "../Headers/get_next_line.h"

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
		all = ft_split_whitepipe(line, minishell);
		minishell->env = ft_pipe(minishell->env, all, minishell);
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

int	ft_line_checker(char *line)
{
	int	i;

	i = 0;
	if (!line)
	{
		ft_rl ();
		return (0);
	}
	else if (line[0] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return (2);
	}
	return (1);
}

int	ft_main_init(int ac, char **av, t_mnsh *minishell)
{
	if (ac > 1 && av[1])
		return (0);
	minishell->exit = 0;
	minishell->memory_blocks = NULL;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_mnsh		minishell;

	if (ft_main_init(ac, av, &minishell) == 0)
		ft_error2(&minishell, 7, NULL);
	minishell.env = ft_file_dup(envp, &minishell);
	while (1)
	{
		ft_signalisation();
		if (isatty(STDIN_FILENO))
			line = readline("ᴍɪɴɪꜱʜᴇʟʟ -> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!ft_line_checker(line) || ft_exit_status(line, &minishell))
			break ;
		if (line[0] == 0 || ft_line_checker(line) == 2)
			continue ;
		ft_execute(line, &minishell);
		add_history(line);
		rl_on_new_line();
		free(line);
	}
	free_path(minishell.env, &minishell);
	free_all_mem(&minishell.memory_blocks);
	return (minishell.exit);
}
