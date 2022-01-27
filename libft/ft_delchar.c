/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:25:13 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 16:12:02 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delchar(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != c)
			j++;
	new = malloc(sizeof(char) * j + 1);
	if (!new)
		return (NULL);
	new[j] = 0;
	while (--i >= 0)
		if (str[i] != c)
			new[--j] = str[i];
	free(str);
	str = ft_strdup(new);
	free(new);
	return (str);
}
