/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:32:39 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/15 23:04:01 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

char	*ft_extr_path(char *line, char **env, t_mnsh *minishell)
{
	char	*path;
	char	**cmds;
	char	**tab;
	t_token	*token;

	tab = ft_split_whitespaces(line, minishell);
	token = ft_lexing(tab, env, minishell);
	cmds = token_create_cmd(token, 0, minishell);
	path = ft_path(ft_file_search_str(env, "PATH=", minishell),
			ft_space_erase(cmds[0], minishell), minishell);
	return (path);
}

char	**ft_chkblt2(char *line, char **env, t_mnsh *minishell)
{
	if (ft_strncmp(line, "export", 6) == 0)
	{
		env = ft_export(&line[7], minishell);
		return (env);
	}
	else if (ft_strncmp(line, "unset", 5) == 0)
	{
		env = ft_unset(ft_file_dup(env, minishell), &line[6], minishell);
		return (env);
	}
	return (env);
}

int	ft_chkblt(char *line, char **env, t_mnsh *minishell)
{
	if (ft_strncmp(line, "cd ", 3) == 0
		|| ft_strncmp(line, "/usr/bin/cd ", 12) == 0)
		ft_cd(line, minishell, &line[3]);
	else if (ft_strncmp(line, "cd\0", 3) == 0
		|| ft_strncmp(line, "/usr/bin/cd\0", 12) == 0)
		ft_cd(line, minishell, NULL);
	else if (ft_strncmp(line, "echo ", 5) == 0
		|| ft_strncmp(line, "/bin/echo ", 10) == 0)
		ft_echo(line, minishell);
	else if (ft_strncmp(line, "pwd", 3) == 0
		|| ft_strncmp(line, "/bin/pwd ", 9) == 0)
		ft_pwd(env, minishell);
	else if (ft_strncmp(line, "env", 3) == 0
		|| ft_strncmp(line, "/usr/bin/env ", 13) == 0)
		ft_env(env);
	else
		return (0);
	return (1);
}

void	ft_chkblt3(char *line, char **env, char *path, t_mnsh *minishell)
{
	int		id;
	int		status;
	char	**new;

	new = ft_cmds_fix(ft_split_whitespaces(line, minishell), minishell);
	if (access(path, F_OK | X_OK))
		ft_error2(minishell, 6, new[0]);
	else
	{
		id = fork();
		if (id == 0)
		{
			minishell->exit = 1;
			if (execve(path, new, ft_file_dup(env, minishell)) == -1)
				ft_error2(minishell, 6, new[0]);
		}
		else
		{
			if (waitpid(id, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char	**ft_builtin(char *line, char **env, t_mnsh *minishell)
{
	int		status;
	int		id;
	char	*path;
	char	**new;

	path = ft_extr_path(line, env, minishell);
	ft_chkblt(line, env, minishell);
	if (ft_strncmp(line, "export", 6) == 0
		|| ft_strncmp(line, "unset", 5) == 0)
		env = ft_chkblt2(line, env, minishell);
	else
		ft_chkblt3(line, env, path, minishell);
	return (env);
}
