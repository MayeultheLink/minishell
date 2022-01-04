/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 20:03:07 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*del_redir(t_lst *lst)
{
	t_lst	*tmp;

	if (lst->token->type == REDIR)
	{
		free(lst->token->str);
		free(lst->token);
		lst = lst->next;
		free(lst->previous);
		lst->previous = NULL;
	}
	while (lst)
	{
		if (lst->previous && lst->token->type == REDIR)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = lst->next->next;
			if (lst->next)
				lst->next->previous = lst;
			free(tmp->token->str);
			free(tmp->token);
			free(tmp);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
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
