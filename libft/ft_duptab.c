/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duptab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:45:34 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 16:10:24 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_duptab(char **tab)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = NULL;
	j = -1;
	while (++j < i)
		new[j] = NULL;
	j = -1;
	while (++j < i)
	{
		new[j] = ft_strdup(tab[j]);
		if (!new)
		{
			ft_freesplit(new);
			return (NULL);
		}
	}
	return (new);
}
