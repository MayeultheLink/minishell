/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:47:22 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 20:17:24 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

# define CMD 0
# define PIPE 1
# define REDIR 2

extern int	g_signal;

typedef struct	s_token
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

typedef struct		s_lst
{
	struct s_token	*token;
	struct s_lst	*previous;
	struct s_lst	*next;
	char			**env;
}			t_lst;

int		is_fake_cmd(char *cmd);
int		heredoc(t_lst *lst);
int		get_cmd_with_arg(t_lst *lst);
int		is_builtin(char *str);
char	*my_getenv(char *str, char **env);
void	free_arg(t_lst *lst);
char	*get_cmd_with_path(t_lst *lst);
char	*get_cmd(t_lst *lst);
int	check_if_cmd(t_lst *lst);
void	freetoken(t_token *token);
t_token	*get_token(char *str, char *control, int beg, int end);
t_lst	*parse_lineofcmd(char *str, char **env);
int		launch_not_interactive(int ac, char **av, char **env);
int		launch_interactive(char **env);
int		exit_minishell(char *str);
void	handler();
int		launch_cmd(char *str, char **env);
int		parse_str(char **str);
char	*deactivate_chars(char *str);
t_lst	*split_lineofcmd(char *str, char *control);
t_lst	*ft_lststart(t_lst *lst);
t_lst	*parse_lst(t_lst *lst, char **env);
char	*error_cmd(t_lst *lst);
int		error_pipe(t_lst *lst);
t_lst	*check_redir(t_lst *lst);
t_lst	*get_arg(t_lst *lst);
int		del_pipes(t_lst *lst);
int		error_redir(t_lst *lst);
void	create_files(t_lst *lst);
int		get_redir(t_lst *lst);
int		cmd(t_lst *lst);
void	freelst(t_lst *lst);
char	*treat_dollar(char *str, char *control, char **env, int trim);
void	echo(char **cmd);
int		cmd_manager(t_lst *cmd_lst, char **env);

#endif
