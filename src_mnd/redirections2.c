/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:26:06 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 18:34:14 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_check_next(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] == '>' && line[*i + 1] == '>')
		{
			*i += 2;
			return (2);
		}
		if (line[*i] == '>' && line[*i + 1] != '>')
		{
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

void	ft_mult_loop(char *line, t_mnsh *minishell)
{
	int	i;
	int	nb;
	int	a;
	int	tmp;

	i = 1;
	a = 0;
	nb = ft_2count(line, '>') + ft_count(line, '>');
	while (i <= nb)
	{
		tmp = ft_check_next(line, &a);
		if (tmp == 2)
			ft_double_greater(ft2_word_after_sign(line, '>',
					i, minishell));
		else if (tmp == 1)
			ft_greather(ft2_word_after_sign(line, '>', i, minishell));
		i++;
	}
	return ;
}

char	**ft_exre_norm(char *line, char **env, t_mnsh *minishell)
{
	if (ft_str2chr(line, '<') && !ft_str2strchr(line, "<<"))
		ft_under(ft_word_after_sign(line, '<', 0, minishell));
	if (ft_str2strchr(line, ">>") && !ft_str2chr(line, '>'))
	{
		ft_dblgrt_loop(line, minishell);
		env = ft_builtin(line, env, minishell);
	}
	if (ft_str2chr(line, '>') && !ft_str2strchr(line, ">>"))
	{
		ft_grt_loop(line, minishell);
		env = ft_builtin(line, env, minishell);
	}
	if (ft_str2strchr(line, ">>") && ft_str2chr(line, '>'))
	{
		ft_mult_loop(line, minishell);
		env = ft_builtin(line, env, minishell);
	}
	return (env);
}

char	**ft_exec_redir(char *line, char **env, t_mnsh *minishell)
{
	int	id;
	int	count;

	count = 0;
	if ((line[0] == '<' && line[1] != '<' ) || line[0] == '>')
		return (0);
	if (ft_str2strchr(line, "<<"))
	{
		ft_dbl_under(line, minishell);
		return (env);
	}
	id = fork();
	if (id == 0)
	{
		env = ft_exre_norm(line, env, minishell);
		exit(0);
	}
	else
		wait(NULL);
	return (env);
}
