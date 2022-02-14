/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:35:18 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 15:18:28 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

typedef struct sigaction	t_sig;
extern int					g_global;

typedef struct s_token
{
	char			*str;
	int				(*tab)[2];
	int				tab_len;
	char			*cpy;
	char			*env_var;
	char			*new_str;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_elem
{
	char			*str;
	t_token			*first_token;
	int				redirect;
	int				heredoc;
	char			*builtin;
	char			*cmd;
	char			*path;
	char			**params;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef struct s_data
{
	t_sig	sig;
	t_elem	*first_elem;
	char	**env;
	char	*input;
	char	*home;
	char	*pwd;
	char	**builtins;
	char	**paths;
	char	quote;
	int		count_pipes;
	int		count_pids;
	int		cpy_stdin;
	int		cpy_stdout;
	int		(*pipes)[2];
	int		*pids;
	int		status;
	char	*last_status;
	int		error;
}			t_data;

void			ft_unlink_heredoc(t_data *data);
void			ft_signals(t_data *data);
void			ft_sig_main(int sig);
t_data			*ft_init_data(void);
void			ft_init_elem(t_elem *elem);
void			ft_init_token(t_token *elem);
void			ft_set_builtins(t_data *data);
int				ft_parsing(t_data *data);
int				ft_check_quotes(char *input, int *i);
void			ft_cpy_envp(t_data *data, char **envp);
int				ft_cpy_elem(t_data *data, char *input, int i, int j);
int				ft_cpy_token(t_data *data, t_elem *elem, int i, int j);
void			ft_add_back_elem(t_data *data, char *str);
void			ft_add_back_token(t_data *data, t_elem *elem, char *str);
int				ft_get_size(void *token, int flag);
void			ft_clear_list(t_data *data);
int				ft_check_syntax(t_data *data);
int				ft_skip_whitespaces(char *str);
void			ft_check_env_var(t_data *data);
int				ft_count_var_len(char *str);
void			ft_find_cmds(t_data *data);
int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, int n);
int				ft_check_whitespaces(char c);
char			*ft_strjoin(t_data *data, char *s1, char *s2, int flag);
char			*ft_strjoin_t(t_data *data, char *s1, char *s2);
char			*ft_strdup_t(t_data *data, char *str, int len);
char			*ft_itoa(t_data *data, int n);
void			ft_split_elem(t_data *data, t_elem *elem, char *str);
char			**ft_split_token(t_data *data, char *str, char **params, \
				int count);
int				ft_expand_var(t_data *data, t_token *token, char *str);
void			ft_supp_quotes(t_data *data, t_elem *elem);
void			ft_supp_quotes_t(t_data *data, t_token *token);
int				ft_count_quotes(char *str);
char			*ft_cpy(t_data *data, char *str, int len);
void			ft_handle_path(t_data *data, t_elem *elem);
char			**ft_split_path(t_data *data, char *str);
void			ft_handle_cmds(t_data *data);
void			ft_handle_builtins(t_data *data, t_elem *elem);
void			ft_check_file(t_data *data, int *fd, char *file);
void			ft_redirection(t_data *data, t_elem *elem, t_token *token);
int				ft_first_cmd(t_data *data, t_elem *first);
void			ft_inter_cmds(t_data *data, t_elem *elem);
void			ft_last_cmd(t_data *data, t_elem *first);
void			ft_redirect_input(t_elem *elem, t_token *token);
void			ft_redirect_heredoc(t_data *data, t_elem *elem);
void			ft_redirect_output(t_elem *elem, t_token *token, int flag);
void			ft_echo(t_data *data, t_elem *elem);
void			ft_cd(t_data *data, t_elem *elem);
void			ft_pwd(t_data *data, int flag);
void			ft_exec(t_data *data, t_elem *elem);
void			ft_export(t_data *data, t_elem *elem);
void			ft_unset(t_data *data, t_elem *elem);
void			ft_env(t_data *data);
void			ft_exit(t_data *data, t_elem *elem);
void			ft_cmd_not_found(t_data *data, t_elem *elem);
void			ft_exit_status(t_data *data);
void			ft_check_malloc(t_data *data, void *str);
void			ft_check_open(int fd, char *str, char *old_str);
void			ft_strerror(t_data *data, char *str);
int				ft_free_child(t_data *data);
int				ft_free(t_data *data);
void			ft_clear_arr(char **arr);
void			ft_free_set_null(char *str);
void			ft_free_pipes_pids(t_data *data);
unsigned char	ft_atouc(char *str);
int				ft_atol(char *str);
int				ft_count_params(char **params);
int				ft_count_var_len(char *str);
int				ft_count_pipes(t_data *data);
int				ft_count_pids(t_data *data);
int				ft_syntax_error(char *ope);
int				ft_skip_quotes(char *str, int *ret);
int				ft_print_export_error(t_data *data, char *param);
int				ft_check_char_export(char *str);
int				ft_find_biggest(t_data *data);
int				ft_find_smallest(t_data *data, int smallest, int biggest, \
				int flag);
int				ft_cmp_env(char *s1, char *s2);
void			ft_print_export(char *str);
int				ft_get_line(t_data *data, char **str, int heredoc);
int				ft_modif_input_heredoc(t_data *data, t_token *token, int i);
int				ft_expand_heredoc(t_data *data, int fd, char *str);
int				ft_check_heredoc(t_data *data, char **str);

#endif