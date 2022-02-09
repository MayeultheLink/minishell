/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/08 16:29:28 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_lst *lst)
{
	if (lst && lst->env)
		ft_freesplit(lst->env);
	lst->env = NULL;
	if (lst && lst->token && lst->token->str)
		free(lst->token->str);
	lst->token->str = NULL;
	if (lst && lst->token)
		free(lst->token);
	lst->token = NULL;
	if (lst)
		free(lst);
	lst = NULL;
}

t_lst	*del_redir(t_lst *lst)
{
	t_lst	*tmp;

	while (lst->token->type == REDIR)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->env)
			lst->env = ft_duptab(tmp->env);
		free_redir(tmp);
		lst->previous = NULL;
	}
	while (lst->next)
	{
		lst = lst->next;
		if (lst->previous && lst->token->type == REDIR)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = tmp->next;
			if (lst->next)
				lst->next->previous = lst;
			free_redir(tmp);
		}
	}
	return (ft_lststart(lst));
}

int	del_spaces(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			lst->token->str = ft_delchar(lst->token->str, ' ');
			if (!lst->token->str)
				return (write(2, "Failed malloc\n", 14), 0);
		}
		lst = lst->next;
	}
	return (1);
}

t_lst	*check_redir(t_lst *lst, int status)
{
	if (!error_redir(ft_lststart(lst)) || !del_spaces(ft_lststart(lst))
		|| !create_files(ft_lststart(lst), status)
		|| !get_redir(ft_lststart(lst)))
		return (freelst(lst), NULL);
	lst = del_redir(ft_lststart(lst));
	return (ft_lststart(lst));
}
