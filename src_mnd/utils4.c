/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:50:29 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/18 22:19:07 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	ft_count_str(char **str)
{
	int	i;

	i = 0;
	while (*str != NULL)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_sper(char *str, int i, int j, t_mnsh *minishell)
{
	char	*ptr;

	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * j + 1);
	j = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_space_erase(char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
	{
		i++;
		j++;
	}
	ptr = ft_sper(str, i, j, minishell);
	return (ptr);
}

char	*ft_space_erase2(char *str, t_mnsh *minishell)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[j])
		j++;
	j--;
	while (str[j] == ' ')
		j--;
	ptr = my_malloc(&minishell->memory_blocks, sizeof(char) * (j - i) + 1);
	k = 0;
	while (i <= j)
	{
		ptr[k] = str[i];
		i++;
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

void	ft_display(char **str)
{
	while (*str)
		dprintf(2, "[%s]\n", *str++);
	dprintf(2, "[%s]\n", *str);
	dprintf(2, "--------------\n");
}
