/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:38:13 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 14:55:47 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_quotes(char *str)
{
	char	q;
	int		i;
	int		c;

	q = 0;
	i = 0;
	c = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!q && (str[i] == '"' || str[i] == '\''))
		{
			q = str[i];
			c++;
		}
		if (q && str[i + 1] == q)
		{
			i++;
			q = 0;
			c++;
		}
		i++;
	}
	return (c);
}

void	del_quotes(char *new, char *delim)
{
	char	q;
	int		i;
	int		j;

	q = 0;
	i = 0;
	j = 0;
	while (delim[i + j])
	{
		if (delim[i + j] == '"' || delim[i + j] == '\'')
		{
			if (!q)
			{
				q = delim[i + j];
				while (delim[i + j + 1] == q)
					j++;
			}
			else if (q == delim[i + j])
				q = 0;
			j++;
		}
		new[i] = delim[i + j];
		if (delim[i + j])
			i++;
	}
}

int	manage_quotes(char *delim, char **new)
{
	char	*trimmed;
	int		i;

	i = check_for_quotes(delim);
	if (!i)
		return (*new = ft_strtrim(delim, " "), 0);
	trimmed = ft_strtrim(delim, " ");
	*new = alloc_with(ft_strlen(trimmed) - i, '0');
	if (!*new)
		return (write(2, "Failed malloc\n", 14), free(trimmed), -1);
	del_quotes(*new, trimmed);
	free(trimmed);
	return (i);
}

char	*parse_str_readline(char *str, t_lst *lst, int status)
{
	char	*parsed_c[2];
	char	*new;
	char	*trash;
	int		i;

	parsed_c[0] = str;
	parsed_c[1] = NULL;
	i = check_for_quotes(&lst->token->str[2]);
	if (!i)
	{
		parsed_c[1] = alloc_with(ft_strlen(str), '0');
		if (!parsed_c[1])
			return (write(2, "Failed malloc\n", 14), free(str), NULL);
		trash = treat_dollar(&new, parsed_c, ft_lststart(lst)->env, status);
		free(trash);
		free(parsed_c[1]);
	}
	else
		new = ft_strdup(str);
	if (!new)
		return (write(2, "Failed malloc\n", 14), free(str), NULL);
	free(str);
	return (new);
}

int	heredoc(t_lst *lst, int status)
{
	int		fd[2];
	char	*str;
	char	*delim;
	int		i;

	pipe(fd);
	i = manage_quotes(&lst->token->str[2], &delim);
	while (i >= 0)
	{
		str = readline("> ");
		if (!str)
			return (close(fd[1]), free(str), free(delim),
				write(2, "heredoc warning : ended by end-of-file\n", 40), fd[0]);
		if (ft_strcmp(delim, str))
		{
			if (!i)
				str = parse_str_readline(str, lst, status);
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
			free(str);
		}
		else
			return (free(delim), free(str), close(fd[1]), fd[0]);
	}
	return (-1);
}
