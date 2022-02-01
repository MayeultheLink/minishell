/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:02:36 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 11:03:11 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_export(t_envlst *lst, int fd)
{
	t_envlst	*node;

	node = lst;
	while (node)
	{
		if (ft_strcmp(node->name, "_"))
		{
			write(fd, "export ", 7);
			write(fd, node->name, ft_strlen(node->name));
			write(fd, "=\"", 2);
			write(fd, node->value, ft_strlen(node->value));
			write(fd, "\"\n", 2);
		}
		node = node->next;
	}
}

int	my_env(t_envlst *lst, int fd)
{
	t_envlst	*node;

	node = lst;
	while (node->next)
	{
		if ((node->value)[0] != '\0' && ft_strcmp(node->name, "?"))
		{
			write(fd, node->env_str, ft_strlen(node->env_str));
			write(fd, "\n", 1);
		}
		node = node->next;
	}
	if (node->value[0] != '\0')
		write(fd, node->env_str, ft_strlen(node->env_str));
	write(fd, "\n", 1);
	return (0);
}

int	my_export(char **cmd, t_envlst **lst, int act, int fd)
{
	int	i;
	int	ret;

	if (!cmd[1])
	{
		write_export(*lst, fd);
		return (0);
	}
	i = 1;
	ret = 0;
	while (act && cmd[i])
	{
		if (set_env(lst, cmd[i]))
			ret = 1;
		i++;
	}
	i = 1;
	while (!act && cmd[i])
	{
		if (check_envname(cmd[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int	my_unset(char **cmd, t_envlst **lst, int act)
{
	int			i;
	t_envlst	*node;

	if (!cmd[1])
		return (0);
	node = NULL;
	i = 1;
	while (act && cmd[i])
	{
		node = find_var(*lst, cmd[i]);
		if (node)
			*lst = del_envnode(*lst, node);
		i++;
	}
	return (0);
}
