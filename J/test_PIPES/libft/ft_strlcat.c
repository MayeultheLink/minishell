/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:03:08 by jpauline          #+#    #+#             */
/*   Updated: 2020/12/15 14:31:49 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst)
		return (size + srclen);
	dstlen = ft_strlen(dst);
	i = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (size + srclen);
	j = 0;
	while (src[j] && (i + j) < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dstlen + srclen);
}
