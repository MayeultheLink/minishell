/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/20 17:46:00 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*parse_lst(t_lst *lst)
{
	t_lst	*lst_start;
	t_lst	*lst_tmp;
	int	i;

	lst_start = lst;
	i = 0;
	while (lst)
	{
		if (lst->token->type == CMD)
		{
			while (lst && lst->token->type == CMD)
			{
				lst = lst->next;
				i++;
			}
		}
		else
			lst = lst->next;
	}
}
