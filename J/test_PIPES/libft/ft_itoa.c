/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:17:24 by jpauline          #+#    #+#             */
/*   Updated: 2021/08/09 19:13:37 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int nbr)
{
	int				len;
	unsigned int	unbr;

	if (nbr == 0)
		return (1);
	len = 0;
	if (nbr < 0)
	{
		len++;
		unbr = -nbr;
	}
	else
		unbr = nbr;
	while (unbr > 0)
	{
		unbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				is_negative;
	unsigned int	unbr;

	len = nbr_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len] = '\0';
	is_negative = 0;
	unbr = n;
	if (n < 0)
	{
		is_negative = 1;
		str[0] = '-';
		unbr = -n;
	}
	while (--len > (is_negative - 1))
	{
		str[len] = unbr % 10 + '0';
		unbr /= 10;
	}
	return (str);
}
