/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:55:20 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:55:22 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/get_next_line.h"

size_t	ft_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check(char *str, int c)
{
	int		i;
	char	uc;

	i = 0;
	uc = (char)c;
	if (!str)
		return (0);
	if (!c)
		return (0);
	while (str[i])
	{
		if (str[i] == uc)
			return (1);
		i++;
	}
	return (0);
}

char	*add(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*ptr;

	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	free(s1);
	return (ptr);
}
