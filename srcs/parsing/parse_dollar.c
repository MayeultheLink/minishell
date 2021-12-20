/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:41:02 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/15 18:14:07 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_env(char *str, int i)
{
	char	*name_env;

        while (str[++i] != ' ' || str[i] == '@')
                ++n;
        name_env = malloc(sizeof(char) * n + 1);
        if (!name_env)
                return (NULL);
        name_env[n] = '\0';
        while (--i >= 0 && --n >= 0)
                name_env[n] = str[i];
	return (name_env);
}

char    *parse_dollar(char *str, int i)
{
	char    *new;
	char    *name_env;
	char    *content_env;
	int     n;
	int     c;

	name_env = get_name_env(str, i);
	if (!name_env)
		return (NULL);
	content_env = getenv(name_env);
	new = malloc(sizeof(char) * (ft_strlen(str) - (ft_strlen(name_env) + 1) + ft_strlen(content_env) + 1));
	if (!new)
	{
		free(name_env);
		return (NULL);
	}
	







	free(name_env);
}

