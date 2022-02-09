/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:47:26 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 14:25:47 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe(t_lst *lst)
{
	if (lst && lst->token && lst->token->str)
	{
		free(lst->token->str);
		lst->token->str = NULL;
	}
	if (lst && lst->token)
	{
		freetoken(lst->token);
		lst->token = NULL;
	}
	if (lst && lst->env)
	{
		ft_freesplit(lst->env);
		lst->env = NULL;
	}
	if (lst)
	{
		free(lst);
		lst = NULL;
	}
}

t_lst	*init_tmp(void)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	if (!tmp)
		return (write(2, "Failed malloc\n", 14), NULL);
	tmp->previous = NULL;
	tmp->next = NULL;
	tmp->env = NULL;
	tmp->token = NULL;
	tmp->token = init_token(NULL, NULL, 0, 0);
	return (tmp);
}

t_lst	*create_blank_cell(t_lst *lst)
{
	t_lst	*tmp;

	if ((lst->token && lst->token->type == PIPE && lst->next
			&& lst->next->token && lst->next->token->type == PIPE))
	{
		tmp = init_tmp();
		tmp->previous = lst;
		tmp->next = lst->next;
		lst->next->previous = tmp;
		lst->next = tmp;
	}
	else if (lst->token && lst->token->type == PIPE && !lst->next)
	{
		tmp = init_tmp();
		tmp->previous = lst;
		lst->next = tmp;
	}
	else if (lst->token && lst->token->type == PIPE && !lst->previous)
	{
		tmp = init_tmp();
		tmp->next = lst;
		lst->previous = tmp;
	}
	return (lst);
}

t_lst	*del_pipes(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		if ((lst->token && lst->token->type == PIPE && lst->next
				&& lst->next->token && lst->next->token->type == PIPE)
			|| (lst->token && lst->token->type == PIPE && !lst->next)
			|| (lst->token && lst->token->type == PIPE && !lst->previous))
			lst = create_blank_cell(lst);
		if (lst->token && lst->token->type == PIPE)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = lst->next->next;
			lst->next->previous = lst;
			free_pipe(tmp);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (ft_lststart(lst));
}

int	error_pipe(t_lst *lst)
{
	if (lst && lst->token && lst->token->type == PIPE)
		return (write(2, "Syntax error : pipe\n", 20), 0);
	while (lst)
	{
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		if (lst->next && lst->next->token->type == PIPE)
			return (write(2, "Syntax error : pipe\n", 20), 0);
		if (!lst->next && lst->token->type == PIPE)
			return (write(2, "Syntax error : pipe\n", 20), 0);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}
