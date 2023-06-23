/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:34:47 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:39:24 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_cmds_count(char **cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0
				|| ft_strncmp(cmd[i], "<\0", 2) == 0)
				i++;
		}
		else
			k++;
		if (!cmd[i])
			break ;
		i++;
	}
	return (k);
}

char	**ft_cmds_fix(char **cmd, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = my_malloc(&minishell->memory_blocks,
			sizeof(char *) * (ft_cmds_count(cmd) + 1));
	while (cmd[i])
	{
		if (ft_strchr_pipe(cmd[i], '>') || ft_strchr_pipe(cmd[i], '<'))
		{
			if (ft_strncmp(cmd[i], ">\0", 2) == 0 || ft_strncmp(cmd[i],
					"<\0", 2) == 0 || ft_strncmp(cmd[i], ">>\0", 3) == 0
				|| ft_strncmp(cmd[i], "<<\0", 3) == 0)
				i++;
		}
		else
			new[j++] = ft_strdup(cmd[i], minishell);
		if (!cmd[i])
			break ;
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = my_malloc(&minishell->memory_blocks,
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = (char)s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_exit_status(char *line, t_mnsh *minishell)
{
	if (ft_strncmp(line, "exit\0", 5) == 0)
		return (1);
	else if (ft_strncmp(line, "exit 0", 6) == 0)
		return (1);
	else if (ft_strncmp(line, "exit 1", 6) == 0)
	{
		minishell->exit = 1;
		if (ft_strncmp(line, "exit 127", 8) == 0)
			minishell->exit = 127;
		else if (ft_strncmp(line, "exit 128", 8) == 0)
			minishell->exit = 128;
		return (1);
	}
	else if (ft_strncmp(line, "exit 2", 6) == 0)
	{
		minishell->exit = 2;
		return (1);
	}
	return (0);
}
