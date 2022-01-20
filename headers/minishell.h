/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:47:22 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/20 15:35:39 by mde-la-s         ###   ########.fr       */
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

extern int	g_g;

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
}				t_token;

typedef struct		s_lst
{
	struct s_token	*token;
	struct s_lst	*previous;
	struct s_lst	*next;
	char			**env;
}			t_lst;

int		launch_cmd(char *str, char **env);
int		parse_str(char **str);
char	*str_control(char *str);
t_lst	*split_minishell(char *str, char *control, char **env);
t_lst	*ft_lststart(t_lst *lst);
t_lst	*parse_lst(t_lst *lst);
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
int		cmd_manager(t_lst *cmd_lst, char **env);

#endif
