/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:32:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/10 17:35:13 by mde-la-s         ###   ########.fr       */
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
		{
			if (q == '"' && str[*i] == '$')
				control[++(*j)] = '0';
			else
				control[++(*j)] = '1';
		}
		if (!str[*i])
		{
			free(control);
			return (NULL);
		}
	}
	else if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		(*i)++;
		control[++(*j)] = '0';
		if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
		{
			(*i)++;
			control[++(*j)] = '0';
		}
		while (str[*i] && str[*i] == ' ')
		{
			(*i)++;
			control[++(*j)] = '1';
		}
	}
	return (control);
}

char	*fill_control(char *control, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (i < (int)ft_strlen(str))
	{
		control = fill_special(str, control, &i, &j);
		if (!control)
		{
			write(1, "Error with quotes\n", ft_strlen("Error with quotes\n"));
			return (NULL);
		}
		control[++j] = '0';
		i++;
	}
	return (control);
}

char	*str_control(char *str)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	new[ft_strlen(str)] = 0;
	new = fill_control(new, str);
	return (new);
}
