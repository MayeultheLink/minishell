/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:20:59 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/13 18:39:17 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != c)
		{
			if (s[i] && s[i] == '"')
			{
				i++;
				while (s[i] != '"')
				{
					if (!s[i])
						return (-1);
					i++;
				}
			}
			else if (s[i] && s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
				{
					if (!s[i])
						return (-1);
					i++;
				}
			}
			i++;
		}
	}
	return (count);
}

int	ft_strlen_split(const char *s, char c, size_t j)
{
	size_t	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s[i + j] && s[i + j] != c)
	{
		if (s[i + j] == '"')
		{
			quotes++;
			i++;
			while (s[i + j] && s[i + j] != '"')
				i++;
			if (!s[i + j])
				return (-1);
			i++;
		}
		else if (s[i + j] == '\'')
		{
			quotes++;
			i++;
			while (s[i + j] && s[i + j] != '\'')
				i++;
			if (!s[i + j])
				return (-1);
			i++;
		}
		if (s[i + j] && s[i + j] != ' ' && s[i + j] != '"' && s[i + j] != '\'')
			i++;
	}
	i -= quotes * 2;
	return (i);
}

char	*ft_fillarray(char *split, const char *s, size_t j, size_t slen)
{
	size_t	i;

	i = -1;
	while (++i < slen)
	{
		if (s[j] == '\'')
		{
			j++;
			while (s[j] != '\'')
			{
				split[i] = s[j];
				i++;
				j++;
			}
			j++;
		}
		else if (s[j] == '"')
		{
			j++;
			while (s[j] != '"')
			{
				split[i] = s[j];
				i++;
				j++;
			}
			j++;
		}
		if (s[j] && s[j] != ' ' && s[j] != '"' && s[j] != '\'')
			split[i] = s[j++];
		else
			i--;
	}
	split[i] = 0;
	return (split);
}

void	*ft_freesplit(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	count;
	size_t	slen;

	i = 0;
	j = 0;
	count = ft_countwords(s, c);
	if (count == -1)
		return (NULL);
	split = malloc(sizeof(char *) * count + 1);
	if (!split || !s)
		return (NULL);
	while (i < count)
	{
		while (s[j] == c)
			j++;
		slen = ft_strlen_split(s, c, j);
		if (slen == -1)
			return (ft_freesplit(split));
		split[i] = malloc(sizeof(char) * slen + 1);
		if (!split[i])
			return (ft_freesplit(split));
		ft_fillarray(split[i], s, j, slen);
		i++;
		while (s[j] && s[j] != c)
		{
			if (s[j] == '\'')
				while (s[j] && s[j] != '\'')
					j++;
			else if (s[j] == '"')
				while (s[j] && s[j] != '"')
					j++;
			j++;
		}
	}
	split[i] = 0;
	return (split);
}
