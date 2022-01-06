/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:26:57 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/06/05 17:13:19 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	if (len < ft_strlen(s))
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	if (start >= ft_strlen(s))
		return (str);
	while (s[i + start] && i < len)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}
