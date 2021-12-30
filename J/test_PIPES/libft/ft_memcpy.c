/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:11:49 by jpauline          #+#    #+#             */
/*   Updated: 2021/08/09 19:23:41 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(s1 + i) = *(char *)(s2 + i);
		i++;
	}
	return (s1);
}
