/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:08:21 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 18:40:08 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_greather(char *file)
{
	int	fdout;

	fdout = openfile(file, 1);
	dup2(fdout, STDOUT_FILENO);
	return ;
}

void	ft_double_greater(char *file)
{
	int	fdout;

	fdout = openfile(file, 2);
	if (!file)
		return ;
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return ;
}

void	ft_grt_loop(char *line, t_mnsh *minishell)
{
	int	i;
	int	nb;

	i = 1;
	nb = ft_count(line, '>');
	while (i <= nb)
	{
		ft_greather(ft2_word_after_sign(line, '>', i, minishell));
		i++;
	}
	return ;
}

void	ft_dblgrt_loop(char *line, t_mnsh *minishell)
{
	int	i;
	int	nb;

	i = 1;
	nb = ft_2count(line, '>');
	while (i <= nb)
	{
		ft_double_greater(ft2_word_after_sign(line, '>', i, minishell));
		i++;
	}
	return ;
}

void	ft_under(char *file)
{
	char	fdin;
	char	tmp[256];

	fdin = openfile(file, 0);
	if (fdin == -1)
	{
		write(2, "minishell: no such file or directory: ", 35);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
		return ;
	}
	read(fdin, &tmp, sizeof(tmp));
	close(fdin);
	printf("%s", tmp);
}
