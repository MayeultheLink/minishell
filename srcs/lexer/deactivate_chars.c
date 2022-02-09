/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deactivate_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:32:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 16:51:48 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_control(char *str, char *contr, int *i, int *j)
{
	char	q;

	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] && (str[*i] == '"' || str[*i] == '\''))
		{
			q = str[*i];
			contr[++(*j)] = '1';
			while (str[++(*i)] && str[*i] != q)
				contr[++(*j)] = '1';
			if (!str[*i])
				return (write(1, "Error with quotes\n", 18), free(contr), NULL);
			contr[++(*j)] = '1';
		}
		if (!str[++(*i)])
			break ;
		else if (str[*i - 1] == '$')
			contr[++(*j)] = '1';
		else
			contr[++(*j)] = '0';
	}
	return (contr);
}

char	*redir(char *str, char *control, int *i, int *j)
{
	if (str[*i] && str[*i] == '<' && str[*i - 1] == '<')
	{
		++(*j);
		while (str[++(*i)] && str[*i] == ' ')
			control[++(*j)] = '1';
		control = heredoc_control(str, control, i, j);
	}
	else if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		++(*j);
		while (str[++(*i)] && str[*i] == ' ')
			control[++(*j)] = '1';
	}
	else
	{
		while (str[*i] && str[*i] == ' ')
		{
			control[++(*j)] = '1';
			++(*i);
		}
	}
	return (control);
}

char	*quotes(char *str, char *control, int *i, int *j)
{
	char	q;

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
	++(*i);
	++(*j);
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
		if (str[*i])
			control = deactivation(str, control, i, j);
	}
	else if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		++(*i);
		++(*j);
		control = redir(str, control, i, j);
		if (!control)
			return (NULL);
		if (str[*i])
			control = deactivation(str, control, i, j);
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
