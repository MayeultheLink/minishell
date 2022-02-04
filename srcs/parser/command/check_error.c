/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:17:04 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/04 14:43:02 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_cmd(t_lst *lst)
{
	char	*str;
	char	**split_path;
	int		i;

	if (is_builtin(lst->token->str) || !(access(lst->token->str, F_OK)))
		return (ft_strdup(lst->token->str));
	split_path = ft_split(getenv("PATH"), ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strcatf(split_path[i], "/", 1);
		split_path[i] = ft_strcatf(split_path[i], lst->token->str, 1);
		if (!access(split_path[i], F_OK))
		{
			str = ft_strdup(split_path[i]);
			ft_freesplit(split_path);
			return (str);
		}
		i++;
	}
	ft_freesplit(split_path);
	return (NULL);
}

int	check_if_cmd(t_lst *lst)
{
	if (!lst->next && lst->token->type == REDIR)
		return (0);
	while (lst)
	{
		if (lst->token->type == CMD)
			return (1);
		if (!lst->next)
		{
			write(2, "Error : no command\n", 19);
			return (-1);
		}
		lst = lst->next;
	}
	return (1);
}
