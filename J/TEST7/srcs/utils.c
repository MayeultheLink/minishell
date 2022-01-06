/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 16:26:05 by mde-la-s         ###   ########.fr       */
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
	if (!lst)
		return (NULL);
	while (lst->previous)
		lst = lst->previous;
	return (lst);
}

void	freelst(t_lst *lst)
{
	t_lst	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (lst->token)
		{
			if (lst->token->str)
				free(lst->token->str);
			if (lst->token->cmd)
				ft_freesplit(lst->token->cmd);
			if (lst->token->redir_in)
				free(lst->token->redir_in);
			if (lst->token->redir_out)
				free(lst->token->redir_out);
			free(lst->token);
		}
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
