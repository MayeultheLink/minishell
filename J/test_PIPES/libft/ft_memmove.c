/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:07:20 by jpauline          #+#    #+#             */
/*   Updated: 2021/08/09 19:24:22 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	if (n == 0)
		return (s1);
	if (s1 > s2)
	{
		i = n;
		while (--i > 0)
			*(unsigned char *)(s1 + i) = *(unsigned char *)(s2 + i);
		*(unsigned char *)(s1 + i) = *(unsigned char *)(s2 + i);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*(unsigned char *)(s1 + i) = *(unsigned char *)(s2 + i);
			i++;
		}
	}
	return (s1);
}
