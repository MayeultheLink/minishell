/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:37:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 11:12:36 by mde-la-s         ###   ########.fr       */
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
	int		i;

	if (!c)
		return (NULL);
	cmd = malloc(sizeof(char *) * (c + 1));
	if (!cmd)
		return (write(2, "Failed malloc\n", 14), NULL);
	cmd[c] = NULL;
	cmd[0] = ft_strdup(lst->token->str);
	if (!cmd[0])
		return (write(2, "Failed malloc\n", 14), NULL);
	lst = lst->next;
	i = 1;
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
		{
			cmd[i] = ft_strdup(lst->token->str);
			if (!cmd[i++])
				return (write(2, "Failed malloc\n", 14), NULL);
		}
		lst = lst->next;
	}
	return (cmd);
}

t_lst	*get_cmd_with_arg2(t_lst *lst)
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
	while (lst->next && lst->token->type != CMD && lst->token->type != PIPE)
		lst = lst->next;
	if (lst->token->type == PIPE)
		lst = lst->previous;
	lst->token->path = get_cmd_with_path(lst);
	lst->token->cmd = fill_cmd(lst, c);
	if (lst->next && lst->next->token->type != PIPE)
		free_arg(lst->next);
	return (lst);
}

int	get_cmd_with_arg(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->str[0] == '/' && access(lst->token->str, F_OK))
		{
			write(2, lst->token->str, ft_strlen(lst->token->str));
			write(2, " : ", 3);
			write(2, "No such file or directory\n", 26);
		}
		lst = get_cmd_with_arg2(lst);
		if (!lst)
			return (0);
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}
