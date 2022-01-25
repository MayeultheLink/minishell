/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:47:26 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/24 16:21:29 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_pipes(t_lst *lst)
{
	t_lst	*tmp;

	while (lst->next)
	{
		if (lst->token->type == PIPE)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = lst->next->next;
			lst->next->previous = lst;
			free(tmp->token->str);
			tmp->token->str = NULL;
			free(tmp->token);
			tmp->token = NULL;
			free(tmp);
			tmp = NULL;
		}
		lst = lst->next;
	}
	return (1);
}

int	error_pipe(t_lst *lst)
{
	if (lst->token->type == PIPE)
	{
		write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
		return (0);
	}
	while (lst)
	{
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		if (lst->next && lst->next->token->type == PIPE)
		{
			write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
			return (0);
		}
		if (!lst->next && lst->token->type == PIPE)
		{
			write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
			return (0);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}
