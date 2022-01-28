/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_with.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:30:27 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/28 16:47:08 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*alloc_with(int d, char c)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (d + 1));
	if (!str)
		return (NULL);
	str[d] = 0;
	i = -1;
	while (++i < d)
		str[i] = c;
	return (str);
}
