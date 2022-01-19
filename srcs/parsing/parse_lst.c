/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/19 16:54:31 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == CMD)
			return (1);
		if (!lst->next)
		{
			write(2, "Error : no command\n", 19);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

t_lst	*parse_lst(t_lst *lst)
{
	if (!lst)
		return (NULL);
	if (!check_cmd(lst))
	{
		freelst(lst);
		return (NULL);
	}
	if (!error_pipe(ft_lststart(lst)))
	{
		freelst(lst);
		return (NULL);
	}
	if (!cmd(ft_lststart(lst)))
		return (NULL);
	lst = check_redir(ft_lststart(lst));
	if (!lst)
		return (NULL);
	if (!del_pipes(ft_lststart(lst)))
	{
		freelst(lst);
		return (NULL);
	}
	return (ft_lststart(lst));
}
