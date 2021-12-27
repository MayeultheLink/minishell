/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/27 16:40:55 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *var, char **env)
{
	char	*result;
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
		{
			result = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(var)));
			if (!result)
				return (NULL);
			j = 0;
			while (env[i][j + ft_strlen(var)])
			{
				result[j] = env[i][j + ft_strlen(var)];
				j++;
			}
			result[j] = 0;
			return (result);
		}
		i++;
	}
	return (NULL);
}

t_lst	*ft_lststart(t_lst *lst)
{
	while (lst->previous)
		lst = lst->previous;
	return (lst);
}
