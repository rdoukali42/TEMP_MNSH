/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:28:35 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/18 20:06:22 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_cwl2(char *str, int *i, int len)
{
	*i += 1;
	len++;
	while (str[*i] != '\'' && str[*i] != '\0' && str[*i] != '\"')
	{
		*i += 1;
		len++;
	}
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		len++;
		*i += 1;
	}
	return (len);
}

int	ft_count_word_len2(char *str, int i)
{
	int		len;

	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			len = ft_cwl2(str, &i, len);
		else if (str[i] != '|')
		{
			i++;
			len++;
		}
		else
			return (len);
	}
	return (len);
}

int	ft_count_words2(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'' || str[i] == '\"')
				ft_count_words_helper(&count, &i, str);
			else if (j > 0)
				count++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	if (j > 0)
		count++;
	return (count);
}

char	**ft_split_whitepipe(char *str, t_mnsh *minishell)
{
	char		**tab;
	t_parsing	vars;

	ft_setenv_helper(&(vars.i), &(vars.j), &(vars.k));
	tab = my_malloc(&minishell->memory_blocks,
			sizeof(char *) * (ft_count_words2(str) + 1));
	while (str[vars.i] != '\0')
	{
		if (str[vars.i] == '|')
			(vars.i)++;
		if (str[vars.i] == '\'' || str[vars.i] == '\"')
		{
			tab[vars.j] = my_malloc(&minishell->memory_blocks,
					sizeof(char) * (ft_count_word_len2(str, vars.i) + 1));
			ft_split_whitespaces_helper1(&vars, tab, str);
		}
		else if (str[vars.i] != '\0')
		{
			tab[vars.j] = my_malloc(&minishell->memory_blocks,
					sizeof(char) * (ft_count_word_len2(str, vars.i) + 1));
			ft_split_whitespipe_helper2(&vars, tab, str);
		}
	}
	tab[vars.j] = 0;
	return (tab);
}
