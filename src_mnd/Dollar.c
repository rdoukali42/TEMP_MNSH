/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:35:23 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/12 11:19:52 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_dollar(char *line, t_mnsh *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], &line[1], ft_strlen(&line[1])) == 0)
		{
			ft_putstr(&minishell->env[i][ft_index(minishell->env[i], '=') + 1]);
			return ;
		}
		i++;
	}
}
