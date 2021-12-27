/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:57:21 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/27 18:15:16 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cmd(t_lst *lst)
{
	char	**split_path;
	int	i;

	split_path = ft_split(getenv("PATH"), ':');
	if (!split_path)
		return (0);
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strcat(split_path[i], "/", 1);
		split_path[i] = ft_strcat(split_path[i], lst->token->str, 1);
		if (!access(split_path[i], F_OK))
		{
			ft_freesplit(split_path);
			return (1);
		}
		i++;
	}
	ft_freesplit(split_path);
	return (0);
}

int	error_redir(t_lst *lst)
{
	int	i;
	int	b;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			i = -1;
			while (lst->token->str[++i])
			{
				b = 0;
				if ((lst->token->str[i] == '<'
					|| lst->token->str[i] == '>')
						&& lst->token->str[i + 1] == ' ')
				{
					b = 1;
					i++;
				}
				while (lst->token->str[i] && lst->token->str[i] == ' ')
					i++;
				if (b == 1 && (!lst->token->str[i]
						|| (lst->token->str[i] == '<' || lst->token->str[i] == '>')))
					return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}

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
