/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:47:28 by mde-la-s          #+#    #+#             */
/*   Updated: 2020/12/16 12:55:01 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*str_src;
	unsigned char	*str_dst;
	size_t			i;

	str_src = (unsigned char *)src;
	str_dst = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		str_dst[i] = str_src[i];
		if (str_dst[i] == (unsigned char)c)
			return (&str_dst[i + 1]);
		i++;
	}
	return (NULL);
}
