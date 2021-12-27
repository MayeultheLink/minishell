/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:37:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/27 18:16:51 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*free_arg(t_lst *lst)
{
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
		{
			free(lst->token->str);
			lst->token->str = NULL;
			lst = lst->previous;
			lst->next = lst->next->next;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

char	**fill_cmd(t_lst *lst, int c)
{
	char	**cmd;
	int	i;

	cmd = malloc(sizeof(char*) * c + 1);
	if (!cmd)
		return (NULL);
	cmd[c] = 0;
	i = 0;
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == CMD)
		{
			(*cmd)[i] = ft_strdup(lst->token->str);
			if (!(*cmd)[i])
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
	lst->token->cmd = fill_cmd(lst, c);
	lst = free_arg(lst->next);
	if (lst->token->type == PIPE)
		return (lst->next);
	return (lst);
}

t_lst	*cmd(t_lst *lst)
{
	while (lst->next)
	{
		lst = get_arg(lst);
		if (!lst)
			return (NULL);
		if (lst->next)
			lst = lst->next;
	}
	if (!error_cmd(ft_lststart(lst)))
		return (NULL);
	return (ft_lststart(lst));
}
