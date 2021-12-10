/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:20:59 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/06/05 16:06:49 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
