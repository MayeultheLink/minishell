/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:47:22 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/20 17:26:30 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

# define CMD 0
# define PIPE 1
# define REDIR 2

typedef struct		s_token
{
	char		*str;
	char		**cmd;
	int		type;
}			t_token;

typedef struct		s_lst
{
	struct s_token	*token;
	struct s_lst	*previous;
	struct s_lst	*next;
}			t_lst;

int		launch_cmd(char *str, char **env);
int		parse_str(char **str);
char	*str_control(char *str);
t_lst	*split_minishell(char *str, char *control);

#endif
