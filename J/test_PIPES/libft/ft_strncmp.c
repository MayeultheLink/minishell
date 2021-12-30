/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:18:47 by jpauline          #+#    #+#             */
/*   Updated: 2020/12/04 15:20:36 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i]) && (s2[i]) && (s1[i] == s2[i]) && (n - 1))
	{
		i++;
		n--;
	}
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
