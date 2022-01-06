/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:13:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 16:55:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_name(char *name, char *str, int i)
{
	int	j;

	name[0] = '/';
	j = 1;
	while (str[i] && str[i] != '<' && str[i] != '>')
		name[j++] = str[i++];
	name = ft_strcat(getcwd(NULL, 0), name, 2);
	return (name);
}

char	**malloc_name(char *str)
{
	char	**name;
	int	c;
	int	i;

	c = 0;
	i = -1;
	while (str[++i])
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] != str[i])
			c++;
	name = NULL;
	name = malloc(sizeof(char*) * (c + 1));
	if (!name)
		return (NULL);
	name[c] = NULL;
	return (name);
}

char	**getname(char *str)
{
	char	**name;
	int	c;
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (str[++i])
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] != str[i])
			k++;
	name = NULL;
	name = malloc(sizeof(char*) * (k + 1));
	if (!name)
		return (NULL);
	name[k] = NULL;
//name = malloc_name(str);
	i = 0;
	j = 0;
	while (j < k)
	{
		while (str[i] == '<' || str[i] == '>')
			i++;
		c = 0;
		while (str[i + c] && str[i + c] != '<' && str[i + c] != '>')
			c++;
		name[j] = malloc(sizeof(char) * (c + 2));
		if (!name[j])
			return (NULL);
		name[j][c + 1] = 0;
		name[j] = fill_name(name[j], str, i);
		while (str[i] && str[i] != '<' && str[i] != '>')
			i++;
		j++;
	}
	return (name);
}

void	create_files(t_lst *lst)
{
	int	fd;
	char	**name;
	int	i;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			name = getname(lst->token->str);
			if (!name)
			{
				write(1, "Error\n", 6);
				return ;
			}
			i = 0;
			while (name[i])
			{
				fd = open(name[i], O_WRONLY | O_CREAT, 0666);
				close(fd);
				i++;
			}
			ft_freesplit(name);
		}
		lst = lst->next;
	}
}
