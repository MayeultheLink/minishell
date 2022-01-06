/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:32:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 16:46:58 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_special(char *str, char *control, int *i, int *j)
{
	char	q;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		control[++(*j)] = '0';
		q = str[*i];
		while (str[++(*i)] && str[*i] != q)
			if (q == '"' && str[*i] == '$')
				control[++(*j)] = '0';
			else
				control[++(*j)] = '1';
		if (!str[*i])
			return (NULL);
	}
	else if ((str[*i] == '<' || str[*i] == '>') && (*i)++)
	{
		control[++(*j)] = '0';
		if ((str[*i] == '<' || str[*i] == '>') && (*i)++)
			control[++(*j)] = '0';
		while (str[*i] == ' ' && (*i)++)
			control[++(*j)] = '1';
	}
	return (control);
}

char	*fill_control(char *control, char *str)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		control = fill_special(str, control, &i, &j);
		control[++j] = '0';
	}
	control[++j] = '\0';
	return (control);
}

char	*str_control(char *str)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	new = fill_control(new, str);
	return (new);
}
