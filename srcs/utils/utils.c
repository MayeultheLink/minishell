/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 13:21:39 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *var, char **env)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
		{
			result = alloc_with(ft_strlen(env[i]) - ft_strlen(var) - 1, '0');
			if (!result)
				return (write(2, "Failed malloc\n", 14), NULL);
			j = 0;
			while (env[i][j + ft_strlen(var) + 1])
			{
				result[j] = env[i][j + ft_strlen(var) + 1];
				j++;
			}
			return (result);
		}
		i++;
	}
	return (ft_strdup("/"));
}

t_lst	*ft_lststart(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->previous)
		lst = lst->previous;
	return (lst);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	is_fake_cmd(char *cmd)
{
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, "..") || !ft_strcmp(cmd, "end"))
		return (1);
	return (0);
}
