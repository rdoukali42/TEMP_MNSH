/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:01:40 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/29 18:20:07 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/pipex.h"
#include "../Headers/memory.h"

void	ft_token_init(char **file, int r, t_token **token, t_mnsh *minishell)
{
	(*token)->str = my_malloc(&minishell->memory_blocks,
			sizeof(char) * 100);
	(*token)->str = file[0];
	(*token)->type = 0;
	(*token)->index = r;
	if (file[1])
	{
		(*token)->next = my_malloc(&minishell->memory_blocks,
				sizeof(t_token));
		*token = (*token)->next;
	}
}

void	ft_token_init2(char **file, int r, t_token **token, t_mnsh *minishell)
{
	(*token)->str = my_malloc(&minishell->memory_blocks,
			sizeof(char) * 100);
	(*token)->str = file[0];
	(*token)->type = 1;
	(*token)->index = r;
	if (file[1])
	{
		(*token)->next = my_malloc(&minishell->memory_blocks,
				sizeof(t_token));
		*token = (*token)->next;
	}
}

void	ft_token_lex(char **file, char **env, t_token **token, t_mnsh *m)
{
	int		i;
	int		r;
	int		tmp;
	char	*p;

	i = 0;
	r = 0;
	tmp = 0;
	while (file[i])
	{
		p = ft_path(ft_file_search_str(env, "PATH=", m), file[i], m);
		if (p != NULL)
		{
			if (tmp == 1)
				r++;
			ft_token_init(&file[i], r, token, m);
			tmp = 1;
		}
		else if (strcmp(file[i], "|") != 0 && strcmp(file[i], " |") != 0
			&& strcmp(file[i], "| ") != 0)
			ft_token_init2(&file[i], r, token, m);
		i++;
		p = NULL;
		my_free(&m->memory_blocks, p);
	}
}

t_token	*ft_lexing(char **file, char **env, t_mnsh *minishell)
{
	t_token	*token;
	t_token	*head;

	token = my_malloc(&minishell->memory_blocks, sizeof(t_token));
	head = token;
	token->index = 0;
	ft_token_lex(file, env, &token, minishell);
	token->next = NULL;
	return (head);
}
