/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/22 16:36:31 by mde-la-s         ###   ########.fr       */
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

t_lst	*del_spaces_redir(t_lst *lst)
{
	char	*new;
	int	i;
	int	j;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			i = -1;
			j = 0;
			while (lst->token->str[++i])
				if (lst->token->str[i] != ' ')
					j++;
			new = malloc(sizeof(char) * j + 1);
			if (!new)
				return (NULL);
			new[j] = 0;
			while (--i >= 0)
				if (lst->token->str[i] != ' ')
					new[--j] = lst->token->str[i];
			free(lst->token->str);
			lst->token->str = ft_strdup(new);
			free(new);
		}
		lst = lst->next;
	}
	return (lst);
}

t_lst	*get_arg(t_lst *lst)
{
	
}

t_lst	*parse_lst(t_lst *lst)
{
	t_lst	*lst_start;

	if (!error_pipe(lst))
		return (NULL);
	lst_start = lst;
	lst = del_spaces_redir(lst);
	if (!lst)
		return (NULL);
	lst = lst_start;
	lst = get_arg(lst);
	if (!lst)
		return (NULL);
	lst = lst_start;
	return (lst);
}
