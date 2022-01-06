/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:49:03 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/06/05 17:24:02 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (s2[i] == 0)
		return ((char *)&s1[i]);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[k + i] && s1[k + i] != s2[j] && i + k < len)
			i++;
		while (s1[k + i] && s2[j] && s1[k + i] == s2[j] && i + k < len)
		{
			j++;
			k++;
		}
		if (s2[j] == 0)
			return ((char *)&s1[i]);
		k = 0;
		i++;
	}
	return (NULL);
}
