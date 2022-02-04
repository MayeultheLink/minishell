/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:17:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/04 19:41:18 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_lst *lst, t_envlst **envlst, int act, int fd)
{
	if (!ft_strcmp(lst->token->cmd[0], "echo"))
		return (my_echo(lst->token->cmd, fd));
	if (!ft_strcmp(lst->token->cmd[0], "cd"))
		return (my_cd(lst->token->cmd, envlst, act));
	if (!ft_strcmp(lst->token->cmd[0], "pwd"))
		return (my_pwd(fd));
	if (!ft_strcmp(lst->token->cmd[0], "export"))
		return (my_export(lst->token->cmd, envlst, act, fd));
	if (!ft_strcmp(lst->token->cmd[0], "unset"))
		return (my_unset(lst->token->cmd, envlst, act));
	if (!ft_strcmp(lst->token->cmd[0], "env"))
		return (my_env(envlst, fd));
	if (!ft_strcmp(lst->token->cmd[0], "exit"))
		my_exit(lst, *envlst, act);
	return (1);
}
