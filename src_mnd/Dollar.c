/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:35:23 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/30 15:49:13 by kmohamed         ###   ########.fr       */
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
	int	j;

	ft_setenv_helper(&i, &j, &j);
	while (line[j] == '$' && line[j + 1] == '$')
	{
		ft_putstr("37708");
		j += 2;
	}
	if (line[j] == '$' && !line[j + 1])
	{
		write(1, &line[j], 1);
		return ;
	}
	while (minishell->env[i] && line[j])
	{
		if (ft_strncmp(minishell->env[i], &line[j + 1],
				ft_strlen(&line[j + 1])) == 0)
		{
			ft_putstr(&minishell->env[i][ft_index(minishell->env[i], '=') + 1]);
			return ;
		}
		i++;
	}
	ft_putstr(&line[j]);
}
