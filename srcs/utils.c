/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/10 16:52:20 by mde-la-s         ###   ########.fr       */
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
	while (lst && lst->previous)
		lst = lst->previous;
	return (lst);
}

void	freelst(t_lst *lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (lst->previous)
		lst = lst->previous;
	while (lst)
	{
		if (lst->token)
		{
			if (lst->token->str)
				free(lst->token->str);
			lst->token->str = NULL;
			if (lst->token->cmd)
				ft_freesplit(lst->token->cmd);
			if (lst->token->redir_in)
				free(lst->token->redir_in);
			lst->token->redir_in = NULL;
			if (lst->token->redir_out)
				free(lst->token->redir_out);
			lst->token->redir_out = NULL;
			free(lst->token);
			lst->token = NULL;
		}
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}
