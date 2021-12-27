/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:58:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/27 20:07:17 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getname(char *str)
{
	char	**name;
	int	c;
	int	i;
	int	j;

	c = 0;
	i = -1;
	while (str[++i])
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] != str[i])
			c++;
	name = malloc(sizeof(char*) * c + 1);
	if (!name)
		return (NULL);
	name[c] = 0;
	i = 0;
	j = 0;
	while (name[j])
	{
		while (str[i] == '<' || str[i] == '>')
			i++;
		c = 0;
		while (str[i + c] && str[i + c] != '<' && str[i + c] != '>')
			c++;
		name[j] = malloc(sizeof(char) * c + 1);
		if (!name[j])
			return (NULL);
		name[j][c] = 0;
		c = 0;
		while (str[i] && str[i] != '<' && str[i] != '>')
			name[j][c++] = str[i++];
		name[j] = ft_strcat(getcwd(NULL), name[j], 2);
		j++;
	}
	return (name);
}

void	create_files(t_lst *lst)
{
	int	fd;
	char	**name;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			name = getname(lst->token->str);
			while (name[i])
			{
				fd = open(name[i], O_CREAT);
				close(fd);
				i++;
			}
			ft_freesplit(name);
		}
		lst = lst->next;
	}
}

t_lst	*get_redir(t_lst *lst)
{
}

t_lst	*del_spaces(t_lst *lst)
{
	char	*new;
	int	i;
	int	j;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			lst->token->str = ft_delchar(lst->token->str, ' ');
			if (!lst->token->str)
				return (NULL);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (ft_lststart(lst));
}

t_lst	*check_redir(t_lst *lst)
{
	if (!error_redir(lst))
		return (NULL);
	lst = del_spaces(lst);
	if (!lst)
		return (NULL);
	create_files(lst);
	lst = get_redir(lst);
	if (!lst)
		return (NULL);
	return (lst);
}
