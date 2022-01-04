/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:47:26 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 20:18:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*del_pipes(t_lst *lst)
{
	t_lst	*tmp;

	while (lst->next)
	{
		if (lst->token->type == PIPE)
		{
			tmp = lst;
			lst = lst->previous;
			lst->next = tmp->next;
			lst->next->previous = lst;
			free(tmp->token->str);
			free(tmp->token);
			free(tmp);
		}
		lst = lst->next;
	}
	return (ft_lststart(lst));
}
