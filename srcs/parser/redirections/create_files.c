/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:13:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 12:55:48 by mde-la-s         ###   ########.fr       */
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
	name = ft_strcatf(getcwd(NULL, 0), name, 3);
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

int	check_for_quotes(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '"')
			c++;
		i++;
	}
	if (c && c % 2 == 0)
		return (1);
	else if (c % 2 == 1)
		return (-1);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			c++;
		i++;
	}
	if (c && c % 2 == 0)
		return (1);
	else if (c % 1 == 1)
		return (-1);
	return (0);
}

char	*del_quotes(char *delim)
{
	char	*new;
	char	q;
	int		i;
	int		j;

	new = malloc(sizeof(char) * ft_strlen(delim) - 1);
	if (!new)
		return (NULL);
	new[ft_strlen(delim) - 2] = 0;
	q = 0;
	i = -1;
	j = 0;
	while (delim[++i + j])
	{
		if (!q && (delim[i + j] == '"' || delim[i + j] == '\''))
		{
			q = delim[i + j];
			j++;
		}
		if (q && !ft_charthere(&delim[i + j + 1], q))
		{
			q = 0;
			j++;
		}
		if (delim[i + j])
			new[i] = delim[i + j];
		else
			break ;
	}
	return (new);
}

int	heredoc(t_lst *lst)
{
	int		fd[2];
	char	*str;
	char	*control;
	char	*delim;
	char	*parsed;
	int		i;

	control = NULL;
	parsed = NULL;
	pipe(fd);
	i = check_for_quotes(&lst->token->str[2]);
	if (i)
		delim = del_quotes(&lst->token->str[2]);
	else
		delim = ft_strdup(&lst->token->str[2]);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			free(str);
			free(delim);
			if (control)
				free(control);
			if (parsed)
				free(parsed);
			write(2, "\nheredoc error : ended by end-of-file\n", 38);
			return (-1);
		}
		if (!i)
		{
			control = alloc_with(ft_strlen(str), '0');
			if (!control)
			{
				free(str);
				free(delim);
				return (0);
			}
			parsed = treat_dollar(str, control, ft_lststart(lst)->env, 0);
		}
		else
			parsed = ft_strdup(str);
		if (ft_strcmp(delim, str))
		{
			write(fd[1], parsed, ft_strlen(parsed));
			write(fd[1], "\n", 1);
		}
		else
		{
			free(str);
			free(control);
			free(parsed);
			free(delim);
			break ;
		}
		free(control);
		free(parsed);
		free(str);
	}
	close(fd[1]);
	return (fd[0]);
}

void	create_files(t_lst *lst)
{
	int		fd;
	char	**name;
	int		i;

	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			if (lst->token->str[0] == '<' && lst->token->str[1] == '<')
				lst->token->fd_redir_in = heredoc(lst);
			else if (lst->token->str[0] == '>')
			{
				name = getname(lst->token->str);
				if (!name)
					return ;
				i = 0;
				while (name[i])
				{
					fd = open(name[i], O_WRONLY | O_CREAT, 0644);
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
