/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/29 15:25:00 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*get_redir(t_lst *lst)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	while (lst->next && lst->token->type != PIPE)
	{
		
	}
	return (ft_lststart(lst));
}

t_lst	*del_spaces(t_lst *lst)
{
	char	*new;
	int	i;
	int	j;

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
	return (lst);
}
