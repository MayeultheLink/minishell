/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:20:59 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/04 12:23:27 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (-1);
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
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		count;
	int		slen;

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
*/

size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

int	ft_strlen_split(const char *s, char c, size_t j)
{
	size_t	i;

	i = 0;
	while (s[i + j] && s[i + j] != c)
		i++;
	return (i);
}

char	*ft_fillarray(char *split, const char *s, size_t j, char c)
{
	size_t	i;

	i = 0;
	while (s[j] != c && s[j])
	{
		split[i] = s[j];
		j++;
		i++;
	}
	split[i] = 0;
	return (split);
}

void	*ft_freesplit(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (NULL);
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

	i = 0;
	j = 0;
	count = ft_countwords(s, c);
	split = malloc(sizeof(char *) * count + 1);
	if (!split || !s)
		return (NULL);
	while (i < count)
	{
		while (s[j] == c)
			j++;
		split[i] = malloc(sizeof(char) * ft_strlen_split(s, c, j) + 1);
		if (!split[i])
			return (ft_freesplit(split));
		ft_fillarray(split[i], s, j, c);
		i++;
		while (s[j] != c && s[j])
			j++;
	}
	split[i] = 0;
	return (split);
}
