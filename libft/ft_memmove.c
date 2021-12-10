/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:59:59 by mde-la-s          #+#    #+#             */
/*   Updated: 2020/12/16 12:56:23 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*str_src;
	unsigned char	*str_dst;
	size_t			i;

	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	i = n;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (i-- > 0)
			str_dst[i] = str_src[i];
	else
	{
		i = 0;
		while (i < n)
		{
			str_dst[i] = str_src[i];
			i++;
		}
	}
	return (str_dst);
}
