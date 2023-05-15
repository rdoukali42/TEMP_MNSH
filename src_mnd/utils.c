/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:49:14 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/15 00:08:00 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_ft2_was(char *str, int *i, int sign, int *k)
{
	*i += 1;
	if (str[*i] == sign)
		*i += 1;
	while (str[*i] != sign && str[*i] != '\0')
		*i += 1;
	if (str[*i] == sign)
		*k += 1;
}

char	*ft_ft2_was2(char *str, int *i, t_mnsh *minishell)
{
	int		start;
	int		j;
	char	*ptr;

	if (strncmp(&str[*i], "/dev/null", 10) == 0)
		return (NULL);
	start = *i;
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t')
		*i += 1;
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * (*i - start + 1));
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

char	*ft2_word_after_sign(char *str, char sign, int index, t_mnsh *minishell)
{
	int		i;
	int		k;
	int		start;
	char	*ptr;

	i = 0;
	k = 1;
	while (str[i] != sign && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] == sign && k != index)
		ft_ft2_was(str, &i, sign, &k);
	if (str[i] == sign && str[i + 1] == sign)
		i += 2;
	else if (str[i] == sign)
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	ptr = ft_ft2_was2(str, &i, minishell);
	return (ptr);
}

int	ft_2count(char *line, char find)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == find && line[i + 1] == find)
		{
			i++;
			k++;
		}
		i++;
	}
	return (k);
}

int	ft_str2strchr(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			if (find[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
