/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:54:10 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/15 22:01:11 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	**ft_file_dup(char **file, t_mnsh *minishell)
{
	char	**new;
	int		i;

	i = 0;
	while (file[i])
		i++;
	new = my_malloc(&minishell->memory_blocks, sizeof(char *) * (i + 1));
	i = 0;
	while (file[i])
	{
		new[i] = ft_strdup(file[i], minishell);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strchr_pipe(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_last_word(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i + 1;
		i++;
	}
	return (&str[j]);
}
