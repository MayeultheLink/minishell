/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:38:13 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 15:25:24 by mde-la-s         ###   ########.fr       */
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

char	*manage_quotes(char *delim)
{
	char	*new;

	if (!check_for_quotes(delim))
		return (ft_strdup(delim));
	else
		new = alloc_with(ft_strlen(delim) - check_for_quotes(delim), '0');
	if (!new)
		return (write(2, "Failed malloc\n", 14), NULL);
	del_quotes(new, delim);
	return (new);
}

char	*parse_str_readline(char *str, t_lst *lst)
{
	char	*parsed;
	char	*control;
	int		i;

	i = check_for_quotes(&lst->token->str[2]);
	if (!i)
	{
		control = alloc_with(ft_strlen(str), '0');
		if (!control)
			return (write(2, "Failed malloc\n", 14), free(str), NULL);
		parsed = treat_dollar(str, control, ft_lststart(lst)->env);
		free(control);
	}
	else
		parsed = ft_strdup(str);
	if (!parsed)
		return (write(2, "Failed malloc\n", 14), free(str), NULL);
	free(str);
	return (parsed);
}

int	heredoc(t_lst *lst)
{
	int		fd[2];
	char	*str;
	char	*delim;

	pipe(fd);
	delim = manage_quotes(&lst->token->str[2]);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (write(2, "\nheredoc error : ended by end-of-file\n", 38),
				free(str), free(delim), -1);
		str = parse_str_readline(str, lst);
		if (ft_strcmp(delim, str))
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
			free(str);
		}
		else
			return (free(delim), free(str), close(fd[1]), fd[0]);
	}
	return (fd[0]);
}
