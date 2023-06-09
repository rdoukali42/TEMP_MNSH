/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:07:32 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 18:40:25 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_count(char *line, char find)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == find && line[i + 1] != find && line[i - 1] != find)
		{
			i++;
			k++;
		}
		i++;
	}
	return (k);
}

char	*ft_ft_was2(char *str, int i)
{
	int		start;
	int		j;
	char	*ptr;

	if (str[i] == '\0')
		return (NULL);
	start = i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	ptr = malloc(sizeof(char) * (i - start + 1));
	j = 0;
	while (str[start] != '\0' && str[start] != ' ' && str[start] != '\t')
	{
		ptr[j] = str[start];
		start++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_word_after_sign(char *str, char sign, int dbl, t_mnsh *minishell)
{
	int		i;
	char	*ptr;

	dbl = minishell->exit;
	i = 0;
	while (str[i] != sign && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	if (str[i] == sign && str[i + 1] == sign)
		i += 2;
	else if (str[i] == sign)
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] == '/' && str[i + 1] == 'd')
		i += 12;
	ptr = ft_ft_was2(str, i);
	return (ptr);
}

char	**ft_exe(char *line, char **env, t_mnsh *minishell)
{
	line = ft_space_erase2(line, minishell);
	if (ft_strchr_pipe(line, '>') || ft_strchr_pipe(line, '<'))
		env = ft_exec_redir(line, env, minishell);
	else
		env = ft_builtin(line, env, minishell);
	return (env);
}
