/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:00:32 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 18:37:59 by mde-la-s         ###   ########.fr       */
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
	int	n;
	int	i;
	int	j;

	n = 1;
	i = 0;
	while (cmd[++i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 1;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
			n++;
		else
			break ;
	}
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(fd, " ", 1);
	}
	if (n == 1)
		write(fd, "\n", 1);
	return (0);
}
