/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:53:41 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/15 16:44:43 by mde-la-s         ###   ########.fr       */
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
	free(str);
	if (!new)
		return (NULL);
	return (new);
}
/*
char	*parse_dollar(char *str, int i, int q)
{
	char	*new;
	char	*name_env;
	char	*content_env;
	int	n;
	int	c;

	while (str[++i] != ' ' || str[i] == '@')
		++n;
	name_env = malloc(sizeof(char) * n + 1);
	if (!name_env)
		return (NULL);
	name_env[n] = '\0';
	while (--i >= 0 && --n >= 0)
		name_env[n] = str[i];
	content_env = getenv(name_env);
	n = 0;
	if (content_env[0] == ' ' && (!q || str[i - 1] == '@'))
		while (content_env[n] == ' ')
			n++;
	c = ft_strlen(content_env);
	if (content_env[--c] == ' ' && (!q || str[i + ft_strlen(name_env) + 1] == '@'))
		while (content)
	n = ft_strlen(str) + (ft_strlen(name_env) - ft_strlen(content_env)) + 1;
	







	free(name_env);
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
				if ((*str)[i] == '$')
					*str = parse_dollar(*str, i, 1);
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
		else if ((*str)[i] == '$')
			*str = parse_dollar(*str, i, 0);
		i++;
	}
	if (!*str)
		return (0);
	return (1);
}
