/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deactivate_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:32:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 19:14:38 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_control(char *str, char *control, int *i, int *j)
{
	char	q;

	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] && (str[*i] == '"' || str[*i] == '\''))
		{
			q = str[*i];
			control[++(*j)] = '1';
			while (str[++(*i)] && str[*i] != q)
				control[++(*j)] = '1';
			if (!str[*i])
				return (write(1, "Error with quotes\n", 18), free(control), NULL);
			control[++(*j)] = '1';
			(*i)++;
		}
		if (!str[*i])
			break ;
		if (str[*i] == '$')
			control[++(*j)] = '1';
		else
			++(*j);
		(*i)++;
	}
	return (control);
}

char	*redir(char *str, char *control, int *i, int *j)
{
	int	heredoc;

	heredoc = 0;
	if (str[*i] && str[*i] == '<' && str[*i - 1] == '<')
		heredoc = 1;
	if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		++(*i);
		++(*j);
		if (heredoc)
			control = heredoc_control(str, control, i, j);
		if (!control)
			return (NULL);
	}
	return (control);
}

char	*quotes(char *str, char *control, int *i, int *j)
{
	char	q;

	++(*j);
	q = str[*i];
	while (str[++(*i)] && str[*i] != q)
	{
		if (q == '"' && str[*i] == '$')
			++(*j);
		else
			control[++(*j)] = '1';
	}
	if (!str[*i])
		return (write(2, "Error with quotes\n", 18), free(control), NULL);
	return (control);
}

char	*deactivation(char *str, char *control, int *i, int *j)
{
	if (str[*i] && (str[*i] == '"' || str[*i] == '\''))
	{
		++(*j);
		control = quotes(str, control, i, j);
		if (!control)
			return (NULL);
	}
	else if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		++(*i);
		++(*j);
		control = redir(str, control, i, j);
		if (!control)
			return (NULL);
	}
	return (control);
}

char	*deactivate_chars(char *str)
{
	char	*control;
	int		i;
	int		j;

	control = alloc_with(ft_strlen(str), '0');
	if (!control)
		return (write(2, "Failed malloc\n", 14), NULL);
	i = 0;
	j = -1;
	while (i < (int)ft_strlen(str))
	{
		control = deactivation(str, control, &i, &j);
		if (!control)
			return (NULL);
		j++;
		i++;
	}
	return (control);
}
