/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:47:26 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/07 11:16:28 by mde-la-s         ###   ########.fr       */
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
			lst->next = tmp->next;
			lst->next->previous = lst;
			free(tmp->token->str);
			free(tmp->token);
			free(tmp);
		}
		lst = lst->next;
	}
	return (1);
}
