/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:16:04 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 13:16:36 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetoken(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		token->str = NULL;
		if (token->path)
			free(token->path);
		token->path = NULL;
		if (token->cmd)
			ft_freesplit(token->cmd);
		if (token->redir_in)
			free(token->redir_in);
		token->redir_in = NULL;
		if (token->redir_out)
			free(token->redir_out);
		token->redir_out = NULL;
		free(token);
		token = NULL;
	}
}

void	freelst(t_lst *lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (lst->previous)
		lst = lst->previous;
	ft_freesplit(lst->env);
	while (lst)
	{
		freetoken(lst->token);
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}
