/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:00:32 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 15:42:25 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(char **cmd, t_envlst **lst, int act)
{
	char	*path;
	int		ret;

	if (!cmd[1] || cmd[2])
	{
		write(2, "cd: arguments error\n", 20);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "cd: getcwd error\n", 17);
		return (1);
	}
	path = ft_strcatf(path, "/", 1);
	path = ft_strcatf(path, cmd[1], 1);
	ret = chdir(path);
	if (ret)
		ret = chdir(cmd[1]);
	if (ret)
		cd_error_message(cmd[1]);
	free(path);
	if (!ret && act)
		ret = update_pwdlst(lst);
	return (ret);
}

int	my_pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
	{
		write(2, "pwd : error\n", 12);
		return (1);
	}
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	return (0);
}

void	cd_error_message(char *str)
{
	write(2, "cd: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
}

int	update_pwdlst(t_envlst **lst)
{
	t_envlst	*node_old;
	char		*path;
	char		*str;

	node_old = find_var(*lst, "PWD");
	str = ft_strcatf("OLDPWD=", node_old->value, 0);
	set_env(lst, str);
	free(str);
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	str = ft_strcatf("PWD=", path, 2);
	set_env(lst, str);
	free(str);
	return (0);
}

int	my_echo(char **cmd, int fd)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		while (cmd[1][i] && cmd[1][i] == 'n')
			i++;
		if (!cmd[1][i])
			n = 1;
	}
	if (n)
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(fd, " ", 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return (0);
}
