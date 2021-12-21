/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/21 17:36:39 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_pipe(t_lst *lst)
{
	if (lst->token->type == PIPE)
		return (0);
	while (lst)
	{
		while (lst && lst->token->type != PIPE)
			lst = lst->next;
		if (!lst)
			return (1);
		if (!lst->next || lst->next->token->type == PIPE)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_lst	*lst_error(t_lst *lst)
{
	if (!error_pipe(lst))
		return (NULL);
}
