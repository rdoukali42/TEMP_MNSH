/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:06:42 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/14 23:34:56 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	**ft_pipefd(t_mnsh *minishell, int c)
{
	int	i;

	i = 0;
	minishell->pipefd = malloc (sizeof(int *) * (c - 1));
	while (i < c - 1)
	{
		minishell->pipefd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < c - 1)
	{
		pipe(minishell->pipefd[i]);
		i++;
	}
	return (minishell->pipefd);
}

void	ft_pipe1(int i, int c, t_mnsh *minishell)
{
	int	j;

	j = 0;
	if (i != 0)
		dup2(minishell->pipefd[i - 1][0], STDIN_FILENO);
	if (i != c - 1)
		dup2(minishell->pipefd[i][1], STDOUT_FILENO);
	while (j < c - 1)
	{
		if (i != j && i != j + 1)
		{
			close(minishell->pipefd[j][0]);
			close(minishell->pipefd[j][1]);
		}
		j++;
	}
}

void	ft_pipe2(int i, int c, t_mnsh *minishell)
{
	if (i != 0)
		close(minishell->pipefd[i - 1][0]);
	if (i != c - 1)
		close(minishell->pipefd[i][1]);
}

void	ft_pipe3(int status, int c, t_mnsh *minishell)
{
	int	j;

	j = 0;
	while (j < c - 1)
	{
		close(minishell->pipefd[j][0]);
		close(minishell->pipefd[j][1]);
		j++;
	}
	if (waitpid(minishell->pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

char	**ft_pipe(char *line, char **env, char **cmd, t_mnsh *minishell)
{
	int		c;
	int		i;
	int		status;

	i = 0;
	c = ft_count_str(cmd);
	ft_pipefd (minishell, c);
	while (i < c)
	{
		minishell->pid = fork();
		if (minishell->pid == -1)
			exit(EXIT_FAILURE);
		else if (minishell->pid == 0)
		{
			ft_pipe1(i, c, minishell);
			env = ft_exe(cmd[i], env, minishell);
			exit(EXIT_FAILURE);
		}
		else
			ft_pipe2(i, c, minishell);
		i++;
	}
	ft_pipe3(status, c, minishell);
	return (env);
}

/*Old _ Version*/
/*char	**ft_pipe(char *line, char **env, char **cmd, t_mnsh *minishell)
{
	int		c;
	int		status;
	minishell->pid_t	minishell->pid;
	int		**pipefd;

	c = ft_count_str(cmd);
	pipefd = ft_pipefd(pipefd, c);
	// pipefd = malloc(sizeof(int *) * (c - 1));
	// for(int i = 0; i < c - 1; i++)
	// 	pipefd[i] = malloc(sizeof(int) * 2);
	// ft_pipefd(pipefd, c);
	// for (int i = 0; i < c - 1; i++)
	// 	pipe(pipefd[i]);
	for (int i = 0; i < c; i++)
	{
		minishell->pid = fork();
		if (minishell->pid == -1) 
			exit(EXIT_FAILURE);
		else if (minishell->pid == 0)
		{
			// if (i != 0)
			// 	dup2(pipefd[i-1][0], STDIN_FILENO);
			// if (i != c-1)
			// 	dup2(pipefd[i][1], STDOUT_FILENO);
			// for (int j = 0; j < c-1; j++)
			// {
			// 	if (i != j && i != j+1)
			// 	{
			// 		close(pipefd[j][0]);
			// 		close(pipefd[j][1]);
			// 	}
			// }
			ft_pipe1(i, c, pipefd);
			env = ft_exe(cmd[i], env, minishell);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i != 0)
				close(pipefd[i-1][0]);
			if (i != c-1)
				close(pipefd[i][1]);
		}
	}
	for (int i = 0; i < c-1; i++)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	if (waitminishell->pid(minishell->pid, &status, 0) == -1)
	{
		perror("waitminishell->pid");
		exit(EXIT_FAILURE);
	}
	return (env);
}
*/