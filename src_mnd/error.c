/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:09:56 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 18:43:05 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_error(t_mnsh *mnsh, int n, char *str)
{
	if (n == 1)
	{
		ft_putstr_fd("No file or Directory\n", 2);
		exit(0);
	}
	else if (n == 2)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(1);
	}
	else if (n == 3)
	{
		ft_putstr_fd("< file1 cmd1 | cmd2 > file2\n", 2);
		exit(0);
	}
	else if (n == 4)
	{
		ft_putstr("minishell: export: ");
		ft_putstr(str);
		ft_putstr(": not a valid identifier\n");
		mnsh->exit = 1;
	}
	else if (n == 5)
		mnsh->exit = errno;
}

void	ft_error2(t_mnsh *minishell, int n, char *str)
{
	if (n == 6)
	{
		ft_putstr("minishell: ");
		ft_putstr(str);
		ft_putstr(": command not found\n");
		minishell->exit = 127;
	}
	if (n == 7)
	{
		ft_putstr("Minishell : Bad Input !\n");
		exit (1);
	}
}
