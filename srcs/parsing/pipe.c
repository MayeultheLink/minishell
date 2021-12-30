/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:47:26 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/30 18:48:55 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*del_pipes(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == PIPE)
		{
			free(lst->token->str);
			lst = lst->previous;
			lst->next = lst->next->next;
		}
	}
	return (ft_lststart(lst));
}
