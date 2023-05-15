/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdoukali <rdoukali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:03:42 by rdoukali          #+#    #+#             */
/*   Updated: 2023/05/15 21:51:55 by rdoukali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <termios.h>

typedef struct s_token
{
	char			*str;
	int				type;
	int				index;
	struct s_token	*next;
}				t_token;

typedef struct s_mnsh
{
	int		id;
	pid_t	pid;
	int		exit;
	int		**pipefd;
	char	*line;
	char	*path;
	char	**cmd;
	char	**env;
	void	*memory_blocks;
}				t_mnsh;

//for ft2_word_after_sign i = dbl, j = index
typedef struct s_parsing
{
	int	i;
	int	j;
	int	k;
}				t_parsing;

///  ///////////////////////////////  ///
///  ///          ERROR          ///  ///
///  ///////////////////////////////  ///
void	ft_error(t_mnsh *mnsh, int n, char *str);
void	ft_error2(t_mnsh *minishell, int n, char *str);
///  ///////////////////////////////  ///
///  ///          SIGNALS       ///  ///
///  ///////////////////////////////  ///
void	kill_fork(int id);
int	exit_cmp(char *str);
void	sin_int_handler(int sig_num);
void	sin_term_handler(int sig_num);
void	signal_handler(int signo);
///  ///////////////////////////////  ///
///  ///          PATHS          ///  ///
///  ///////////////////////////////  ///
char	*ft_path(char *path, char *cmd, t_mnsh *minishell);
char	*ft_file_search_str(char **file, char *str, t_mnsh *minishell);
char	*str_extr(char *str, int n, t_mnsh *minishell);
char	*str_extr_norm(char *str, int n, int tmp, t_mnsh *minishell);
char	*ffss_norm(char **file, int i, int j, t_mnsh *minishell);
///  ///////////////////////////////  ///
///  ///          BUILTINS       ///  ///
///  ///////////////////////////////  ///
char	**ft_builtin(char *line, char **env, t_mnsh *minishell);
void	ft_echo(char *line, t_mnsh *minishell);
void	ft_cd(char *line, t_mnsh *minishell, char *parm);
char	**ft_export(char *str, t_mnsh *minishell);
char	**ft_unset(char **env, char *str, t_mnsh *minishell);
char	**ft_exec_redir(char *line, char **env, t_mnsh *minishell);
char	**ft_pipe(char *line, char **env, char **cmd, t_mnsh *minishell);
///  ///////////////////////////////  ///
///  ///          LIBFT          ///  ///
///  ///////////////////////////////  ///
size_t	ft_strlen(const char *str);
int		ft_strlen2(const char *str);
char	*ft_strjoin(char const *s1, char const *s2, t_mnsh *minishell);
char	**ft_split(char const*s, char c, t_mnsh *env);
void	ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
void	free_path(char **path, t_mnsh *minishell);
char	*ft_strdup(char *str, t_mnsh *minishell);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
int		ft_strchr(char *str, char c);
char	*ft_strdup2(char *str, t_mnsh *minishell);
char	**ft_file_dup(char **file, t_mnsh *minishell);
char	*ft_search_and_return(char **env, char *str, t_mnsh *minishell);
char	*ft_last_word(char *str);
char	**ft_add_str_to_file(char *str, t_mnsh *minishell);
char	**ft_split_whitespaces(char *str, t_mnsh *minishell);
int		ft_str2strchr(char *str, char *find);
int		ft_count_str(char **str);
///  ///////////////////////////////  ///
///  ///          UTILS          ///  ///
///  ///////////////////////////////  ///
char	**ft_unset_env(char **env, char *str, t_mnsh *minishell);
char	**ft_exe(char *line, char **env, t_mnsh *minishell);
char	**token_create_cmd(t_token *token, int n, t_mnsh *minishell);
char	*ft_getenv(char *str, t_mnsh *minishell);
int		ft_setenv(char *name, char *value, t_mnsh *minishell);
void	ft_pwd(char **env, t_mnsh *minishell);
void	ft_env(char **env);
void	ft_putstr(char *str);
void	ft_dollar(char *line, t_mnsh *minishell);
int		openfile(char *file, int perm);
char	**ft_cmds_fix(char **cmd, t_mnsh *minishell);
char	*ft_readline(char *str, char c, t_mnsh *minishell);
void	ft_quote(char *line, char **env, char c, t_mnsh *minishell);
void	ft_dbl_under(char *line, t_mnsh *minishell);
void	ft_display(char **str);
int		ft_count_str(char **str);
char	*ft2_word_after_sign(char *str, char sign, int index, t_mnsh *minishell);
char	*ft_word_after_sign(char *str, char sign, int dbl, t_mnsh *minishell);
int		ft_str2chr(char *str, char c);
int		ft_count(char *line, char find);
int		ft_2count(char *line, char find);
int		ft_strchr_pipe(char *str, char c);
char	*ft_space_erase2(char *str, t_mnsh *minishell);
char	*ft_space_erase(char *str, t_mnsh *minishell);
///  ///////////////////////////////  ///
///  ///          echo           ///  ///
///  ///////////////////////////////  ///
void	ft_putstr_noquote(char *str);
int		ft_quote_count(char *str);
int		ft_check_quote(char *line, char c);
char	*ft_quote_erase(char *str, t_mnsh *minishell);
char	*ft_quote_chk(char *str, t_mnsh *env);
///  ///////////////////////////////  ///
///  ///          env            ///  ///
///  ///////////////////////////////  ///
char	*ft_strdup_without_str(char *str, char *to_remove, t_mnsh *env);
void	ft_search_and_add(char *find, char *cpy, t_mnsh *minishell);
///  ///////////////////////////////  ///
///  ///          Helpers        ///  ///
///  ///////////////////////////////  ///
void	ft_setenv_helper(int *i, int *j, int *k);
void	ft_putstr_fd(char *s, int fd);
void	free_path(char **path, t_mnsh *minishell);
int		ft_str2chr(char *str, char c);
void	ft_putchar(char c);
int		ft_strlen2(const char *str);
void	ft_putnbr(int num);
void	loop_cmd(int *i, char	**cmd, char	*fix, t_mnsh	*minishell);
void	init_ft_quote_count(int *i, int *a, int *b, int *c);
int		env_helper(char *str, char *to_remove, char	*new);
void	ft_count_words_helper(int *count, int *i, char *str);
void	ft_split_whitespaces_helper1(t_parsing *vars, char	**tab, char *str);
void	ft_split_whitespaces_helper2(t_parsing *vars, char	**tab, char *str);
void	ft_file_name_helper1(int *i, char *line);
void	ft_stradd_helper(char *p, char const *s1, int *i);
void	ft_stradd_helper2(char *line, int *i, int *j, int *r);
int		ft_stradd_helper3(char *line, int *i);
void	ft_stradd_helper4(char *name, char *line, int *j, int *r);
void	ft_mult_loop(char *line, t_mnsh *minishell);

void	ft_under(char *file);
void	ft_dblgrt_loop(char *line, t_mnsh *minishell);
void	ft_grt_loop(char *line, t_mnsh *minishell);
void	ft_double_greater(char *file, int fdout);
void	ft_greather(char *file, int fdout);

t_token	*ft_lexing(char **file, char **env, t_mnsh *minishell);
#endif