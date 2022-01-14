/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:18:48 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/14 11:47:33 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
}

char	**dup_env(char **env)
{
	char	**new;
	int		c;

	c = 0;
	while (env[c])
		c++;
	new = malloc(sizeof(char*) * (c + 1));
	if (!new)
		return (NULL);
	new[c] = NULL;
	while (--c >= 0)
	{
		new[c] = ft_strdup(env[c]);
		if (!new[c])
		{
			while (new[++c])
				free(new[c]);
			free(new);
			return (NULL);
		}
	}
	return (new);
}
