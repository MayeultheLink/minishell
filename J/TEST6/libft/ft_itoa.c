/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:39:19 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/06/05 16:03:48 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nblen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			i;
	unsigned int	n_uns;

	i = ft_nblen(n);
	n_uns = n;
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n_uns *= -1;
	}
	s[i] = 0;
	i -= 1;
	while (n_uns >= 10)
	{
		s[i] = (n_uns % 10) + 48;
		n_uns /= 10;
		i--;
	}
	s[i] = n_uns % 10 + 48;
	return (s);
}
