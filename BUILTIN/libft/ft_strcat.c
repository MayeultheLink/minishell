/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:55 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 16:11:56 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcatf(char *str1, char *str2, int f)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		str[j++] = str2[i++];
	str[j] = '\0';
	if (f == 1)
		free(str1);
	if (f == 2)
		free(str2);
	if (f == 3)
	{
		free(str1);
		free(str2);
	}
	return (str);
}
