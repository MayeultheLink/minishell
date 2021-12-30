/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:48:52 by jpauline          #+#    #+#             */
/*   Updated: 2021/08/09 19:22:05 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s1 + i) = *(unsigned char *)(s2 + i);
		if (*(unsigned char *)(s2 + i) == (unsigned char)c)
			return (s1 + i + 1);
		i++;
	}
	return (NULL);
}
