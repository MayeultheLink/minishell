/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:57:21 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/20 21:00:59 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_cmd(t_lst *lst)
{
	char	*str;
	char	**split_path;
	int	i;

	if (!ft_strcmp(lst->token->str, "echo") || !ft_strcmp(lst->token->str, "cd")
		|| !ft_strcmp(lst->token->str, "pwd") || !ft_strcmp(lst->token->str, "export")
		|| !ft_strcmp(lst->token->str, "unset") || !ft_strcmp(lst->token->str, "env")
		|| !ft_strcmp(lst->token->str, "exit"))
		return (ft_strdup(lst->token->str));
	if (!(access(lst->token->str, F_OK)))
		return(ft_strdup(lst->token->str));
	split_path = ft_split(getenv("PATH"), ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strcat(split_path[i], "/", 1);
		split_path[i] = ft_strcat(split_path[i], lst->token->str, 1);
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

int	error_redir(t_lst *lst)
{
	int	i;
	int	b;
	int	c;

	while (lst)
	{
		c = 0;
		if (lst->token->type == REDIR)
		{
			i = 0;
			while (lst->token->str[i])
			{
				b = 0;
				if (lst->token->str[i] == '<' || lst->token->str[i] == '>')
				{
					c++;
					if (!lst->token->str[i + 1] || lst->token->str[i + 1] == ' ')
					{
						b = 1;
						i++;
					}
				}
				if (c > 2)
				{
					write(2, "Syntax error : redirections\n", ft_strlen("Syntax error : redirections\n"));
					return (0);
				}
				while (lst->token->str[i] && lst->token->str[i] == ' ')
					i++;
				if (b == 1 && (!lst->token->str[i]
						|| (lst->token->str[i] == '<' || lst->token->str[i] == '>')))
				{
					write(2, "Syntax error : redirections\n", ft_strlen("Syntax error : redirections\n"));
					return (0);
				}
				if (lst->token->str[i])
					i++;
			}
		}
		lst = lst->next;
	}
	return (1);
}

int	error_pipe(t_lst *lst)
{
	if (!lst)
		return (0);
	if (lst->token->type == PIPE)
	{
		write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
		return (0);
	}
	while (lst)
	{
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		if (lst->next && lst->next->token->type == PIPE)
		{
			write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
			return (0);
		}
		if (!lst->next && lst->token->type == PIPE)
		{
			write(2, "Syntax error : pipe\n", ft_strlen("Syntax error : pipe\n"));
			return (0);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (1);
}
