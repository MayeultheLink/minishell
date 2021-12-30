/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 01:24:10 by jpauline          #+#    #+#             */
/*   Updated: 2020/12/11 19:51:55 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;
	int				nw;

	if (n < 0)
	{
		write(fd, "-", 1);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	nw = nbr % 10 + '0';
	write(fd, &nw, 1);
}
