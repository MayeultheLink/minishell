/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:23:00 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/06/05 16:01:29 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*src;
	size_t			i;

	src = malloc(size * count);
	if (!src)
		return (NULL);
	if (count == 0 || size == 0)
		return (src);
	i = 0;
	while (i < count * size)
	{
		src[i] = 0;
		i++;
	}
	return (src);
}
