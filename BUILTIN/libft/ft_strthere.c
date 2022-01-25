/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strthere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:14:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 12:16:18 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strthere(char *str, char *there)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str, there, ft_strlen(there)))
			return (1);
		i++;
	}
	return (0);
}
