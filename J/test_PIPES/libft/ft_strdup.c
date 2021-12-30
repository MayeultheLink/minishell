/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:34:58 by jpauline          #+#    #+#             */
/*   Updated: 2021/08/09 19:26:47 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	i;
	size_t	srclen;

	if (!s1)
		return (NULL);
	srclen = ft_strlen(s1);
	dest = (char *)malloc(sizeof(*dest) * (srclen + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < (srclen + 1))
		dest[i] = s1[i];
	return (dest);
}
