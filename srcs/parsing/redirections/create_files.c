/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:13:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/19 16:51:26 by mde-la-s         ###   ########.fr       */
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
	name = ft_strcat(getcwd(NULL, 0), name, 3);
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
	{
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] != str[i])
		{
			if (i && str[i] == '<' && str[i - 1] == '<')
				k--;
			k++;
		}
	}
	name = NULL;
	name = malloc(sizeof(char*) * (k + 1));
	if (!name)
		return (NULL);
	name[k] = NULL;
	i = 0;
	j = 0;
	while (j < k)
	{
		while (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i - 1] == '<' && str[i] == '<')
				while (str[i + c] && str[i + c] != '<' && str[i + c] != '>')
					i++;
		}
		c = 0;
		while (str[i + c] && str[i + c] != '<' && str[i + c] != '>')
			c++;
		name[j] = malloc(sizeof(char) * (c + 2));
		if (!name[j])
		{
			ft_freesplit(name);
			return (NULL);
		}
		name[j][c + 1] = 0;
		name[j] = fill_name(name[j], str, i);
		if (!name[j])
		{
			ft_freesplit(name);
			return (NULL);
		}
		while (str[i] && str[i] != '<' && str[i] != '>')
			i++;
		j++;
	}
	return (name);
}

int	heredoc(char *delim)
{
	int		fd[2];
	char	*str;

	pipe(fd);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			write(2, "\nheredoc error : ended by end-of-file\n", 38);
			return (-1);
		}
	//	str = treat_dollar(str, str_control(str), env, 0);
		if (ft_strcmp(delim, str))
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
		}
		else
		{
			free(str);
			break ;
		}
		free(str);
	}
	close(fd[1]);
	return (fd[0]);
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
			if (lst->token->str[0] == '<' && lst->token->str[1] == '<')
				lst->token->fd_redir_in = heredoc(&lst->token->str[2]);
			else if (lst->token->str[0] == '>')
			{
				name = getname(lst->token->str);
				if (!name)
					return ;
				i = 0;
				while (name[i])
				{
					fd = open(name[i], O_WRONLY | O_CREAT, 0666);
					if (fd > -1)
						close(fd);
					i++;
				}
				ft_freesplit(name);
			}
		}
		lst = lst->next;
	}
}
