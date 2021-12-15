/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:30:42 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/15 11:51:19 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_cmd(char **split_str, char **split_path, char **env)
{
	int	i;

	if (!ft_strcmp("exit", split_str[0]))
	{
		write(1, "exit\n", 5);
		return (0);
	}
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strcat(split_path[i], "/", 1);
		split_path[i] = ft_strcat(split_path[i], split_str[0], 1);
		if (!access(split_path[i], F_OK))
			break ;
		i++;
	}
	if (split_path[i] && fork() == 0)
		execve(split_path[i], split_str, env);
	if (split_path[i])
		wait(NULL);
	return (1);
}

int	launch_cmd(char *str, char **env)
{
	char	**split_str;
	char	**split_path;
	int		i;

	split_path = ft_split(getenv("PATH"), ':');
	split_str = ft_split(str, ' ');
	if (split_str && split_path)
	{
		i = exe_cmd(split_str, split_path, env);
		ft_freesplit(split_str);
		ft_freesplit(split_path);
		return (i);
	}
	else
		write(1, "Error\n", 6);
	if (split_str)
		ft_freesplit(split_str);
	if (split_path)
		ft_freesplit(split_path);
	return (1);
}
