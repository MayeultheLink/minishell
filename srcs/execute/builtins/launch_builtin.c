/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:17:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 15:43:56 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(char **cmd, t_envlst **envlst, int act, int fd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (my_echo(cmd, fd));
	if (!ft_strcmp(cmd[0], "cd"))
		return (my_cd(cmd, envlst, act));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (my_pwd(fd));
	if (!ft_strcmp(cmd[0], "export"))
		return (my_export(cmd, envlst, act, fd));
	if (!ft_strcmp(cmd[0], "unset"))
		return (my_unset(cmd, envlst, act));
	if (!ft_strcmp(cmd[0], "env"))
		return (my_env(*envlst, fd));
	return (1);
}
