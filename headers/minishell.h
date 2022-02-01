/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:47:22 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 16:44:52 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>

# define CMD 0
# define PIPE 1
# define REDIR 2

extern int	g_signal;

typedef struct s_token
{
	char		*str;
	char		*path;
	char		**cmd;
	int			builtin;
	char		*redir_in;
	int			type_redir_in;
	int			fd_redir_in;
	char		*redir_out;
	int			type_redir_out;
	int			type;
	int			echo;
}				t_token;

typedef struct s_lst
{
	struct s_token	*token;
	struct s_lst	*previous;
	struct s_lst	*next;
	char			**env;
}			t_lst;

typedef struct s_envlst
{
	char			*name;
	char			*value;
	char			*env_str;
	struct s_envlst	*next;
}			t_envlst;

typedef struct s_manag
{
	int	cmd_nbr;
	int	*tab_fd;
	int	*tab_pid;
	int	fd_file_in;
	int	fd_file_out;
	int	i;
}			t_manag;

int			check_if_cmd(t_lst *lst);
t_lst		*check_redir(t_lst *lst, int status);
void		close_all_fd(int *tab_fd, int n);
int			cmd(t_lst *lst);
int			cmd_count(t_lst *cmd_lst);
int			cmd_manager(t_lst *cmd_lst, char ***env, t_envlst **envlst);
int			create_files(t_lst *lst, int status);
int			*create_tab_fd(int n);
int			*create_tab_pid(int n);
char		*deactivate_chars(char *str);
int			del_pipes(t_lst *lst);
char		*error_cmd(t_lst *lst);
int			error_pipe(t_lst *lst);
int			error_redir(t_lst *lst);
int			exit_minishell(char *str, char **env, t_envlst *envlst);
int			free_and_wait(t_manag *man);
void		free_arg(t_lst *lst);
void		freelst(t_lst *lst);
void		freetoken(t_token *token);
t_lst		*ft_lstend(t_lst *lst);
t_lst		*ft_lststart(t_lst *lst);
t_lst		*get_arg(t_lst *lst);
char		*get_cmd(t_lst *lst);
int			get_cmd_with_arg(t_lst *lst);
char		*get_cmd_with_path(t_lst *lst);
int			get_redir(t_lst *lst);
t_token		*get_token(char *str, char *control, int beg, int end);
void		handler(int keysym);
int			heredoc(t_lst *lst, int status);
t_manag		*init_man(void);
int			init_tab_fd(int **tab_fd, int cmd_nbr, int **tab_pid);
int			is_builtin(char *str);
int			is_fake_cmd(char *cmd);
int			launch_cmd(char *str, char **env);
int			launch_not_interactive(int ac, char **av, t_envlst *lst);
int			launch_interactive(t_envlst *lst);
char		*my_getenv(char *str, char **env, int status);
t_lst		*parse_lineofcmd(char *str, char **env, int status);
t_lst		*parse_lst(t_lst *lst, char **env, int status);
int			parse_str(char **str);
void		redirections(int *fd_file_in, int *fd_file_out, t_lst *node);
t_lst		*split_lineofcmd(char *str, char *control, char **env, int status);
char		*treat_dollar(char *str, char *control, char **env, int status);
int			wait_all_pid(int *tab, int n);
int			launch_builtin(char **cmd, t_envlst **envlst, int act, int fd);
char		**ft_split_env(char *str);
int			is_envname(char *str);
void		free_envnode(t_envlst *node);
int			check_envname(char *str);
t_envlst	*new_envnode(char *env, t_envlst *lst);
t_envlst	*free_envlst(t_envlst *lst, t_envlst *ret);
t_envlst	*init_envlst(char **env);
t_envlst	*ins_envlst(t_envlst *node, t_envlst *sorted);
t_envlst	*sort_envlst(t_envlst *lst);
t_envlst	*find_var(t_envlst *lst, char *var);
t_envlst	*del_envnode(t_envlst *lst, t_envlst *node);
int			set_env(t_envlst **lst, char *str);
int			envlst_len(t_envlst *lst);
char		**make_envtab(char **env, t_envlst *lst);
void		write_export(t_envlst *lst, int fd);
int			my_env(t_envlst **lst, int fd);
int			my_echo(char **cmd, int fd);
int			my_export(char **cmd, t_envlst **lst, int act, int fd);
int			my_pwd(int fd);
void		cd_error_message(char *str);
int			update_pwdlst(t_envlst **lst);
int			my_cd(char **cmd, t_envlst **lst, int act);
int			my_unset(char **cmd, t_envlst **lst, int act);

#endif
