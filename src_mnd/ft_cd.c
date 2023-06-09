/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:44:36 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 21:43:21 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*ft_getenv(char *str, t_mnsh *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], str, ft_strlen(str)) == 0)
			return (ft_strdup(&minishell->env[i][ft_strlen(str)], minishell));
		i++;
	}
	return (NULL);
}

void	ft_chdir(int ch, char *path, t_mnsh *minishell)
{
	char	*tmp;
	char	*tmp2;

	if (ch == -1)
	{
		minishell->exit = 1;
		ft_putstr("minishell: cd: ");
		ft_putstr(path);
		ft_putstr(": No such file or directory\n");
	}
	else
	{
		tmp = ft_getenv("PWD=", minishell);
		ft_search_and_add("OLDPWD=", tmp, minishell);
		tmp2 = getcwd(NULL, 0);
		ft_search_and_add("PWD=", tmp2, minishell);
		free(tmp2);
		tmp = ft_getenv("PWD=", minishell);
	}
}

void	ft_cd(t_mnsh *minishell, char *parm)
{
	char	*path;
	char	*tmp;

	path = NULL;
	while (*parm == ' ')
		parm++;
	if (parm == NULL || *parm == '\0')
		path = ft_strdup(ft_getenv("HOME=", minishell), minishell);
	else if (ft_strncmp(parm, "-", 1) == 0)
	{
		tmp = ft_getenv("OLDPWD=", minishell);
		if (tmp == NULL)
			ft_putstr("cd: OLDPWD not set\n");
		else
			path = ft_strdup(tmp, minishell);
	}
	else if (ft_strncmp(parm, "~", 1) == 0)
		path = ft_strdup(ft_getenv("HOME=", minishell), minishell);
	else if (ft_strncmp(parm, ".\0", 2) == 0)
		path = ft_strdup(ft_getenv("PWD=", minishell), minishell);
	else
		path = ft_strdup(parm, minishell);
	ft_chdir(chdir(path), path, minishell);
	my_free(&minishell->memory_blocks, path);
}
