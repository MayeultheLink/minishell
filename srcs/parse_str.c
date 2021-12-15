/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:53:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/15 15:11:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_chevron(char *str, int i)
{
	char	*new;
	int	c;

	c = i + 1;
	while (str[i + 1] == ' ')
	{
		while (str[c])
		{
			str[c] = str[c + 1];
			c++;
		}
		c = i + 1;
	}
	new = ft_strdup(str);
	if (!new)
		return (NULL);
	free(str);
	return (new);
}
/*
char	*parse_dollar(char *str)
{
	
}*/

int	quotes(char **str, int i)
{
	if ((*str)[i] == '\'')
	{
		i++;
		while ((*str)[i] && (*str)[i] != '\'')
			i++;
	}
	else if ((*str)[i] == '"')
	{
		i++;
		while ((*str)[i] && (*str)[i] != '"')
		{
//				if ((*str)[i] == '$')
//					*str = parse_dollar(*str, i);
			i++;
		}
	}
	if (!*str)
		return (-1);
	return (i);
}

int	parse_str(char **str)
{
	int	i;

	i = 0;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			i = quotes(str, i);
		else if (((*str)[i] == '<' || (*str)[i] == '>')
				&& (*str)[i + 1] == ' ')
			*str = parse_chevron(*str, i);
//		else if ((*str)[i] == '$')
//			*str = parse_dollar(*str, i);
		i++;
	}
	if (!*str)
		return (0);
	return (1);
}
