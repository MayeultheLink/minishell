/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:18:48 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/16 16:43:55 by mde-la-s         ###   ########.fr       */
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

void	export(char **cmd, char **env)
{
	int	i;
	int	j;
	int	e;
//	int	b;

	i = 1;
	while (cmd[i])
	{
		if (ft_isnum(cmd[i][0]))
		{
			write(2, "export: invalid identifier\n", 27);
			return ;
		}
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '=')
		{
			if (!ft_isalnum(cmd[i][j]))
			{
				write(2, "export: invalid identifier\n", 27);
				return ;
			}
			j++;
		}
//		b = 0;
//		if (cmd[1][i + 1] == '\'')
//			b = 1;
		e = 0;
		while (env[e])
			e++;
		env[e] = ft_strdup(cmd[i]);
		env[e] = ft_delchar(env[e], '"');
		if (!env[e])
			return (NULL);
		env[e + 1] = malloc(sizeof(char*));
		if (!env[e + 1])
			return (NULL);
		env[e + 1] = NULL;
		i++;
	}
	if (i == 1)
		env(env);
}

char	***dup_env(char **env)
{
	char	***new;
	int		c;
	int		i;
	int		j;

	new = malloc(sizeof(char**) * 3);
	if (!new)
		return (NULL);
	new[2] = NULL;
	c = 0;
	while (env[c])
		c++;
	new[0] = malloc(sizeof(char*) * (c + 1));
	if (!new[0])
		return (NULL);
	new[0][c] = NULL;
	new[1] = malloc(sizeof(char*) * (c + 1));
	if (!new[1])
		return (NULL);
	new[1][c] = NULL;
	c--;
	i = 0;
	while (env[c][i] && env[c][i] != '=')
	{
		new[0][c][i] = env[c][i];
		i++;
	}
	j = 0;
	while (env[c][i] && env[c][i + 1])
	{
		i++;
		new[1][c][j] = env[c][i];
		j++;
	}


	while (--c >= 0)
	{
		new[c] = ft_strdup(env[c]);
		if (!(*new)[c])
		{
			while ((*new)[++c])
				free((*new)[c]);
			free(new);
			return (NULL);
		}
	}
	return (new);
}
