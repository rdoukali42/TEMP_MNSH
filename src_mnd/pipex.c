/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:58:48 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:45:15 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

int	openfile(char *file, int perm)
{
	int	res;

	if (perm == 0)
	{
		res = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
			ft_error(NULL, 1, NULL);
	}
	if (perm == 1)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (perm == 2)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (res == -1)
		exit(0);
	return (res);
}
