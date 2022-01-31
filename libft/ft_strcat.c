/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:55 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/31 20:23:30 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strcat(char *str1, char *str2, int f)
{
	if (f == 1)
		free(str1);
	if (f == 2)
		free(str2);
	if (f == 3)
	{
		free(str1);
		free(str2);
	}
}

char	*ft_strcatf(char *str1, char *str2, int f)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (free_strcat(str1, str2, f), NULL);
	i = 0;
	j = 0;
	while (str1[i])
		str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		str[j++] = str2[i++];
	str[j] = '\0';
	free_strcat(str1, str2, f);
	return (str);
}
