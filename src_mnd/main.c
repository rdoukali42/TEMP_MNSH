/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:42:38 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/18 22:34:05 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	**ft_exe(char *line, char **env, t_mnsh *minishell)
{
	line = ft_space_erase2(line, minishell);
	if (ft_strchr_pipe(line, '>') || ft_strchr_pipe(line, '<'))
		env = ft_exec_redir(line, env, minishell);
	else
		env = ft_builtin(line, env, minishell);
	return (env);
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
		all = ft_split_whitepipe(line, minishell);
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

int	ft_line_checker(char *line)
{
	if (!line)
	{
		ft_rl ();
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_mnsh		minishell;

	minishell.exit = 0;
	minishell.memory_blocks = NULL;
	minishell.env = ft_file_dup(envp, &minishell);
	while (1)
	{
		ft_signalisation();
		line = readline("ᴍɪɴɪꜱʜᴇʟʟ -> ");
		if (!ft_line_checker(line))
			break ;
		if (line[0] == 0)
			continue ;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		ft_execute(line, &minishell);
		add_history(line);
		rl_on_new_line();
		free(line);
	}
	free_path(minishell.env, &minishell);
	free_all_mem(&minishell.memory_blocks);
	system("leaks minishell");
	return (minishell.exit);
}
