/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:54:55 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:55:05 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/get_next_line.h"

char	*fil_buf(int fd, char *str)
{
	int		nb;
	char	*buf;

	nb = 2;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while ((!(check(str, '\n')) && nb != 0))
	{
		nb = read(fd, buf, BUFFER_SIZE);
		if (nb == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nb] = '\0';
		if (!str)
		{
			str = (char *)malloc(sizeof(char) * 1);
			str[0] = '\0';
		}
		str = add(str, buf);
	}
	free(buf);
	return (str);
}

char	*fil_to_nl(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i - 1] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (buf[j - 1] != '\n')
	{
		str[j] = buf[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*fil_all(char *buf)
{
	int		i;
	char	*str;

	i = 0;
	if (!buf[i])
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_len(buf) + 1));
	if (!str)
		return (NULL);
	while (buf[i])
	{
		str[i] = buf[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*buff_rest(char	*buf)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (buf[i] != '\n')
		i++;
	ptr = malloc(sizeof(char) * (ft_len(buf) - i));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
	{
		ptr[j] = buf[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	free(buf);
	return (ptr);
}

char	*get_next_line(int fd)
{
	char		*ptr;
	static char	*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	buffer = fil_buf(fd, buffer);
	if (!buffer)
		return (NULL);
	if (check(buffer, '\n'))
		ptr = fil_to_nl(buffer);
	else
		ptr = fil_all(buffer);
	if (!check(buffer, '\n'))
	{
		free(buffer);
		buffer = NULL ;
	}
	else
		buffer = buff_rest(buffer);
	return (ptr);
}
