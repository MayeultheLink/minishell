/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/06 15:29:26 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_redir(t_lst *lst)
{
	t_lst	*tmp;

	while (lst->token->type == REDIR)
	{
		free(lst->token->str);
		free(lst->token);
		tmp = lst;
		lst = lst->next;
		lst->previous = NULL;
		free(tmp);
	}
	while (lst)
	{
		if (lst->previous && lst->token->type == REDIR)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = tmp->next;
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
}

int	del_spaces(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			lst->token->str = ft_delchar(lst->token->str, ' ');
			if (!lst->token->str)
				return (0);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}

int	check_redir(t_lst *lst)
{
	if (!error_redir(ft_lststart(lst)) || !del_spaces(ft_lststart(lst)))
		return (0);
	create_files(ft_lststart(lst));
	if (!get_redir(ft_lststart(lst)))
		return (0);
	del_redir(ft_lststart(lst));
	return (1);
}
