/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:17:04 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/07 11:06:17 by mde-la-s         ###   ########.fr       */
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
