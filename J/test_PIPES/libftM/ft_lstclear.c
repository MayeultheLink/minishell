/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:13:13 by mde-la-s          #+#    #+#             */
/*   Updated: 2020/12/16 18:17:12 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		lst_tmp = *lst;
		*lst = lst_tmp->next;
		free(lst_tmp);
	}
	*lst = NULL;
}
