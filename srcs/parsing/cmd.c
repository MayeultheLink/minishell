/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:37:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/19 16:39:54 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(t_lst *lst)
{
	t_lst	*tmp;

	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = tmp->next;
			if (lst->next)
				lst->next->previous = lst;
			free(tmp->token->str);
			tmp->token->str = NULL;
			free(tmp->token);
			tmp->token = NULL;
			free(tmp);
			tmp = NULL;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
}

char	**fill_cmd(t_lst *lst, int c)
{
	char	**cmd;
	int	i;

	cmd = malloc(sizeof(char*) * (c + 1));
	if (!cmd)
		return (NULL);
	cmd[c] = NULL;
	i = 0;
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
		{
			if (i == 0)
			{
				cmd[0] = ft_strdup(lst->token->str);
				if (!cmd[0])
					return (NULL);
				lst->token->path = error_cmd(lst);
				if (!lst->token->path)
				{
					write(2, "Command not found : ", 20);
					write(2, lst->token->str, ft_strlen(lst->token->str));
					write(2, "\n", 1);
					ft_freesplit(cmd);
					return (NULL);
				}
				if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "cd")
					|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
					|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
					|| !ft_strcmp(cmd[0], "exit"))
					lst->token->builtin = 1;
				else
					lst->token->builtin = 0;
			}
			if (i)
				cmd[i] = ft_strdup(lst->token->str);
			if (!cmd[i])
				return (NULL);
			i++;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (cmd);
}

t_lst	*get_arg(t_lst *lst)
{
	int	c;

	c = 0;
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
			c++;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	while (lst->previous && lst->previous->token->type != PIPE)
		lst = lst->previous;
	while (lst->next && lst->token->type != CMD)
		lst = lst->next;
	lst->token->cmd = NULL;
	lst->token->cmd = fill_cmd(lst, c);
	if (!lst->token->cmd)
	{
		freelst(ft_lststart(lst));
		return (NULL);
	}
	if (lst->next && lst->next->token->type != PIPE)
		free_arg(lst->next);
	while (lst->next && lst->token->type != PIPE)
		lst = lst->next;
	return (lst);
}

int	cmd(t_lst *lst)
{
	while (lst)
	{
		lst = get_arg(lst);
		if (!lst)
			return (0);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}
