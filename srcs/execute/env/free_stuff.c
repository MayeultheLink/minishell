/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:38 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 11:16:22 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*free_envlst(t_envlst *lst, t_envlst *ret)
{
	if (lst->next)
		free_envlst(lst->next, ret);
	free_envnode(lst);
	return (ret);
}

void	free_envnode(t_envlst *node)
{
	free(node->name);
	free(node->value);
	free(node->env_str);
	free(node);
}
