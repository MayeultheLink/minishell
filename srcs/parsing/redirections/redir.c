/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/30 19:01:42 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*del_redir(t_lst *lst)
{
	if (lst->token->type == REDIR)
	{
		free(lst->token->str);
		lst = lst->next;
		lst->previous = NULL;
	}
	else
		lst = lst->next;
	while (lst->next)
	{
		if (lst->token->type == REDIR)
		{
			free(lst->token->str);
			lst = lst->previous;
			lst->next = lst->next->next;
			lst->next->previous = lst;
		}
		lst = lst->next;
	}
	if (lst->token->type == REDIR)
	{
		free(lst->token->str);
		lst = NULL;
	}
	return (ft_lststart(lst));
}

t_lst	*del_spaces(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			lst->token->str = ft_delchar(lst->token->str, ' ');
			if (!lst->token->str)
				return (NULL);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (ft_lststart(lst));
}

t_lst	*check_redir(t_lst *lst)
{
	if (!error_redir(lst))
		return (NULL);
	lst = del_spaces(lst);
	if (!lst)
		return (NULL);
	create_files(lst);
	lst = get_redir(lst);
	if (!lst)
		return (NULL);
	lst = del_redir(lst);
	if (!lst)
		return (NULL);
	return (lst);
}
